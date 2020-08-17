#-*-coding:utf-8-*-
import random
import socket
from Crypto import Random
from Crypto.PublicKey import RSA
from Crypto.Cipher import AES
from Crypto.Cipher import PKCS1_v1_5 as Cipher_pkcs1_v1_5
import base64

# client, server share password
pw = "12345678"

class prpcrypt():
    def __init__(self, key):
        if len(key)<16:
            key=key+(16-len(key))*"\0"
        self.key = key[:16]
        self.mode = AES.MODE_CBC

    def encrypt(self, text):
        cryptor = AES.new(self.key, self.mode, IV=self.key)
        length = 16
        count = len(text)
        add=count % length
        if add:
            text = text + ('\0' * (length-add))
        self.ciphertext = cryptor.encrypt(text)
        return base64.b64encode(self.ciphertext)

    def decrypt(self, text):
        cryptor = AES.new(self.key, self.mode, IV=self.key)
        plain_text = cryptor.decrypt(base64.b64decode(text))
        return plain_text.rstrip('\0')

# random generate
random_generator = Random.new().read
rsa = RSA.generate(1024, random_generator)

# generate pk and sk
pk = rsa.publickey().exportKey()
skS = rsa.exportKey()

address = ('127.0.0.1', 8088)
socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
socket.connect(address)

print "pk: " + pk

socket.send('server')
data = socket.recv(1024)
if data == "no":
    print "connect error"
    socket.close()
    exit(-1)

# send pk encrypted with pw
pc = prpcrypt(pw)
e = pc.encrypt(pk)
socket.send(e)

# decrypte to get Ks
data = socket.recv(1024)
pc = prpcrypt(pw)
Ks1 = pc.decrypt(data)
rsakey = RSA.importKey(skS)
cipher = Cipher_pkcs1_v1_5.new(rsakey)
Ks = cipher.decrypt(base64.b64decode(Ks1), random_generator)
print "Ks: " + Ks

# randomly generate NC and send it to client with Ks encryption
a = [random.randint(0,9) for _ in range(10)]
NC = ''.join(str(i) for i in a)
print "NC: " + NC
pc = prpcrypt(Ks)
e = pc.encrypt(NC)
socket.send(e)

data = socket.recv(1024)
pc = prpcrypt(Ks)
N1_2 = pc.decrypt(data)
print 'N1_2: '+N1_2
if N1_2.find(NC) == 0:
    print "Authentication success"
else:
    print "Authentication faild"

# Ks encrypted N2 sent to client
N2 = N1_2[len(NC):]
pc = prpcrypt(Ks)
e = pc.encrypt(N2)
socket.send(e)

while True:
    data = raw_input(">")
    if data == "quit":
        socket.send(data)
        break
    try:
        socket.send(data)
    except Exception, e:
        print "Server Abnormal Exit"
        break
    data = socket.recv(1024)
    print "Server say: " + data
socket.close()