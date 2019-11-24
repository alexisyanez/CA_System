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
    print('CBR:' + cbr.decode("utf-8") +' NBR:'+ nbr.decode("utf-8")+ ' NTIB:' + ntib.decode("utf-8")+' NN:'+nn.decode("utf-8"))
    print(type(cbr))
    print(type(nbr))
    print(type(ntib))
    print(type(nn))
    
    nn=float(nn.decode("utf-8"))
    print(type(nn))
    CBR=float(cbr.decode("utf-8"))
    NBR=float(nbr.decode("utf-8"))
    NTIB=float(ntib.decode("utf-8"))	
    if nn < 60:
        print('Low Density Chosen with NN:'+str(nn))
        X=[[CBR],[NBR],[NTIB]]
        X2=list(map(list, zip(*X)))
        X1=np.asarray(X2)
        X1=np.expand_dims(X1,-1)

        Desc = model_Low.predict(X1)
        Desc = np.argmax(Desc,axis=-1)
        client.sendall(Desc[0].tobytes())
        print('El valor del descriptor es: ')
        print(Desc)
    else:
        print('High Density Chosen with NN:'+str(nn))
        Desc = model_High.predict([CBR,NBR,NTIB])
        Desc = np.argmax(Desc,axis=-1)
        client.send(str(Desc))
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
