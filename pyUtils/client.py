#!/usr/bin/python3           # This is client.py file

import socket
from sys import argv

#creando socket
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

#estableciendo conexión
server.connect(('127.0.0.1', 6670))

#Obteniendo métricas de entrada
cond = ' '.join(argv[1:])

#Enviando métricas
server.send(cond.encode('ascii'))

#Recibiendo Resultado de ANN
reci = server.recv(1024) #.decode('ascii')

#Decodificando mensaje
Desc1 = reci.decode('ascii') #int(Desc,0)

#transformarlo en int
Desc= int(Desc1)

#Cerrando conexión
server.close()

#enviando int
print(Desc)

#Debugging


#print(type(Desc))
#print('Valores de Omnet++')
#print(cond)
#print('valores desde la ANN')
#print("Descriptor= %i" % Desc)

######################
#reci2 = reci.split()
#reci3 = int.from_bytes(reci2,"big") #reci2[0].decode("ascii")
#print(type(reci2))
#Desc = int.from_bytes(reci3[0],"big")
