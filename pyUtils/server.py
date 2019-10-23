import socket
from math import floor
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server.bind(('127.0.0.1', 6670))
server.listen(1)
while True:
    client, clientAddress = server.accept()
    req = client.recv(150)
    cbr, ntib, nbr = req.split()
    if cbr+ntib+nbr >= 0:
    	Desc = cbr+ntib+nbr
    	client.send(str(Desc))    
    	print 'El Valor del descriptor es: '
    	print Desc + '\n'
    else:
    	print 'Desc es menor que cero \n'         
print '[*] Clossing connection...'
client.close()
server.close()