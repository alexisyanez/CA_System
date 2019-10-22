import socket
from sys import argv

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.connect(('127.0.0.1', 6670))
cond = ' '.join(argv[1:])
server.send(cond)
Ptx = server.recv(10)
server.close()
print Ptx