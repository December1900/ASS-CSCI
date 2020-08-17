# -*-coding:utf-8-*-
import os
import random
import socket
from Crypto.Cipher import AES
from Crypto.Cipher import PKCS1_v1_5 as Cipher_pkcs1_v1_5
import base64
import threading
from Crypto.PublicKey import RSA

# client, server share password
dict = {}
dict["server"] = "12345678"


class prpcrypt():
    def __init__(self, key):
        if len(key) < 16:
            key = key + (16 - len(key)) * "\0"
        self.key = key[:16]
        self.mode = AES.MODE_CBC

    def encrypt(self, text):
        cryptor = AES.new(self.key, self.mode, IV=self.key)
        length = 16
        count = len(text)
        add = count % length
        if add:
            text = text + ('\0' * (length - add))
        self.ciphertext = cryptor.encrypt(text)
        return base64.b64encode(self.ciphertext)

    def decrypt(self, text):
        cryptor = AES.new(self.key, self.mode, IV=self.key)
        plain_text = cryptor.decrypt(base64.b64decode(text))
        return plain_text.rstrip('\0')


def mytarget(connect):

    # authentication
    user = connect.recv(1024)
    if user in dict:
        connect.send("yes")
        pw = dict[user]
        print "user is " + user
    else:
        connect.send("no")
        print "user error"
        connect.close()
        exit(-1)

    # decrypt to get pk 
    ra = connect.recv(1024)
    pc = prpcrypt(pw)
    pk = pc.decrypt(ra)
    print 'pk: ' + pk

    # randomly generate the session key Ks, and send it to the server with double encryption
    a = [random.randint(0, 9) for _ in range(10)]
    Ks = ''.join(str(i) for i in a)
    print "Ks: " + Ks
    rsakey = RSA.importKey(pk)
    cipher = Cipher_pkcs1_v1_5.new(rsakey)
    cipher_text = base64.b64encode(cipher.encrypt(Ks))
    pc = prpcrypt(pw)
    e = pc.encrypt(cipher_text)
    connect.send(e)

    # decrypt NC, randomly generate NS
    data = connect.recv(1024)
    pc = prpcrypt(Ks)
    NC = pc.decrypt(data)
    print 'NC: ' + NC
    a = [random.randint(0, 9) for _ in range(10)]
    NS = ''.join(str(i) for i in a)

    # encrypt NC || NS with Ks and send to server
    NC_B = NC + NS
    pc = prpcrypt(Ks)
    e = pc.encrypt(NC_B)
    connect.send(e)

    # decrypt N2, judge whether N2 is equal to NS
    data = connect.recv(1024)
    pc = prpcrypt(Ks)
    N2 = pc.decrypt(data)
    if N2 == NS:
        print "N2 is equal to NS"
        print "Authentication success"
    else:
        print "Authentication faild"

    while True:
        try:
            data = connect.recv(1024)
        except Exception, e:
            print "User Abnormal Exit"
            exit(-1)
        if data == "quit":
            print "User " + user + " quit!"
            break
        print "User " + user + " say: " + data
        connect.send("receive " + data)
    connect.close()


address = ('127.0.0.1', 8088)
socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
socket.bind(address)
socket.listen(5)

while True:
    connect, addr = socket.accept()
    print 'Connected From', addr
    chat = threading.Thread(target=mytarget, args=(connect,))
    chat.start()