import socket
import socks 
import requests

socks.set_default_proxy(socks.SOCKS5, "127.0.0.1", 8848, username=None, password=None)
socket.socket = socks.socksocket
print(requests.get('http://www.baidu.com').text)