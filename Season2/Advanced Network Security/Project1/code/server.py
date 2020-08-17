import select
import socket
import struct
from socketserver import StreamRequestHandler, ThreadingTCPServer
SOCKS_VERSION = 5

class Socks5Proxy(StreamRequestHandler):
    def handle(self):
        print('Accepting connection from {}'.format(self.client_address))

        # read 2 bytes data from client
        header = self.connection.recv(2)
        version, nmethods = struct.unpack("!BB", header)
        
        # set socks5, nmethods
        assert version == SOCKS_VERSION
        assert nmethods > 0

        # 1.Get authentication method
        methods = self.get_methods(nmethods)
        
        # 2.Select method 0x00(NO AUTHENTICATION REQUIRED)
        if 0 not in set(methods):
            self.server.close_request(self.request)
            return
        self.connection.sendall(struct.pack("!BB", SOCKS_VERSION, 0))

        # 3.Requests
        version, cmd, _, address_type = struct.unpack("!BBBB", self.connection.recv(4))
        assert version == SOCKS_VERSION
        # DST.ADDR 
        # IPv4
        if address_type == 1:  
            address = socket.inet_ntoa(self.connection.recv(4))
        # Domain name       
        elif address_type == 3:  
            domain_length = self.connection.recv(1)[0]
            address = self.connection.recv(domain_length)
        # IPV6
        elif address_type == 4:  
            addr_ip = self.connection.recv(16)
            address = socket.inet_ntop(socket.AF_INET6, addr_ip)
        else:
            self.server.close_request(self.request)
            return
        port = struct.unpack('!H', self.connection.recv(2))[0]

        # Response to only connect 0x01
        try:
            if cmd == 1: 
                remote = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                remote.connect((address, port))
                bind_address = remote.getsockname()
                print('Connected to {} {}'.format(address, port))
            else:
                self.server.close_request(self.request)
            addr = struct.unpack("!I", socket.inet_aton(bind_address[0]))[0]
            port = bind_address[1]

          
		    # VER, CMD, RSV, ATYP, ADDR, PORT
            reply = struct.pack("!BBBBIH", SOCKS_VERSION, 0, 0, 1, addr, port)
        except Exception as err:
            logging.error(err)

            reply = self.failed_reply(address_type, 5)
        self.connection.sendall(reply)

        # connect success, change data
        if reply[1] == 0 and cmd == 1:
            self.exchange_loop(self.connection, remote)
        self.server.close_request(self.request)

    
    def get_methods(self, n):
        methods = []
        for i in range(n):
            methods.append(ord(self.connection.recv(1)))
        return methods

    def failed_reply(self, address_type, error_number):
        return struct.pack("!BBBBIH", SOCKS_VERSION, error_number, 0, address_type, 0, 0)

    def exchange_loop(self, client, remote):
        while True:
            r, w, e = select.select([client, remote], [], [])
            if client in r:
                data = client.recv(4096)
                if remote.send(data) <= 0:
                    break
            if remote in r:
                data = remote.recv(4096)
                if client.send(data) <= 0:
                    break


if __name__ == '__main__':
    # use ThreadingTCPServer to strat proxy 
    with ThreadingTCPServer(('127.0.0.1', 8848), Socks5Proxy) as server:
        server.serve_forever()