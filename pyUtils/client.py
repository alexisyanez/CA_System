import socket
from sys import argv

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.connect(('127.0.0.1', 6670))
cond = ' '.join(argv[1:])
server.sendall(cond.encode('utf-8'))
Desc = server.recv(10)
server.close()
print('Valores de Omnet++ \n')
print(cond)
print('\n valores desde la ANN \n')
print(Desc)