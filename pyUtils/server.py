#!/usr/bin/python3           # This is server.py file

import tensorflow as tf
#from tensorflow import keras
#from keras.models import Sequential
#from keras import keras_models
#import keras
#from keras.models import load_model
import h5py
import numpy as np
from matplotlib import pyplot as plt

# load model
model_Low =tf.keras.models.load_model('model_LowDen.h5')
# summarize model.
model_Low.summary()
plt.show()
# load model
model_High = tf.keras.models.load_model('model_HighDen.h5')
# summarize model.
model_High.summary()
plt.show()


import socket
from math import floor
print('Go to server code')
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server.bind(('127.0.0.1', 6670))
server.listen(1)
while True:
    client, clientAddress = server.accept()
    req = client.recv(150)
    cbr, ntib, nbr, nn = req.split()
    print('CBR:' + cbr.decode('ascii') +' NBR:'+ nbr.decode('ascii')+ ' NTIB:' + ntib.decode('ascii')+' NN:'+nn.decode('ascii'))
    print(type(cbr))
    print(type(nbr))
    print(type(ntib))
    print(type(nn))
    
    nn=float(nn.decode('ascii'))
    print(type(nn))
    CBR=float(cbr.decode('ascii'))
    NBR=float(nbr.decode('ascii'))
    NTIB=float(ntib.decode('ascii'))	
    if nn < 60:
        print('Low Density Chosen with NN:'+str(nn))
        X=[[CBR],[NBR],[NTIB]]
        X2=list(map(list, zip(*X)))
        X1=np.asarray(X2)
        X1=np.expand_dims(X1,-1)

        Desc1 = model_Low.predict(X1)
        Desc1 = np.argmax(Desc1,axis=-1)
        Desc1 = str(Desc1[0])
        client.send(Desc1.encode('ascii'))#bytes([Desc1])
        print('El valor del descriptor es: ')
        print(Desc1)
    else:
        print('High Density Chosen with NN:'+str(nn))
        Desc = model_High.predict([CBR,NBR,NTIB])
        Desc = np.argmax(Desc,axis=-1)
        client.send(str(1))#Desc))
        print('El valor del descriptor es: ')
        print(Desc)
#    if cbr+ntib+nbr >= 0:
#    	Desc = cbr+ntib+nbr
#    	client.send(str(Desc))
#    	print ('El Valor del descriptor es: ')
#    	print (Desc + '\n')
#    else:
#    	print ('Desc es menor que cero \n')
#print ('[*] Clossing connection...')
client.close()
server.close()
