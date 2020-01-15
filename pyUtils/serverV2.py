#!/usr/bin/python3           # This is server.py file

#import tensorflow as tf
#from tensorflow import keras
#from keras.models import Sequential
#from keras import keras_models
#import keras
#from keras.models import load_model
#import h5py
import sys
import numpy as np
import h2o
import pandas as pd
from h2o.automl import H2OAutoML
from matplotlib import pyplot as plt

# load AutoML model Low Density
h2o.init()

model_Low = h2o.load_model('XGBoost_grid_1_AutoML_20191206_032959_model_2_LD')

# summarize model.
model_Low

# load AutoML model High Density
model_High = h2o.load_model('XGBoost_grid_1_AutoML_20191206_034436_model_2_HD')
# summarize model.
model_High



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
   #print(type(cbr))
   #print(type(nbr))
   # print(type(ntib))
   # print(type(nn))
    nn=float(nn.decode('ascii'))
   # print(type(nn))
    CBR=float(cbr.decode('ascii'))
    NBR=float(nbr.decode('ascii'))
    NTIB=float(ntib.decode('ascii'))
    X=[CBR,NBR,NTIB]
    X=np.asarray(X)
    X=np.expand_dims(X,-1)
    X=np.transpose(X)
    DATA = pd.DataFrame(X,columns=['CBR','NBR','NTIB'])
    hf = h2o.H2OFrame(DATA)

    if nn < 80:
        print('Low Density Chosen with NN:'+str(nn))
        model_perf = model_Low.predict(hf)
        #model_perf
        m=model_perf.as_data_frame().values
        Desc1 = m[0][0]
        #Desc1 = np.argmax(Desc1,axis=-1)
        Desc1 = int(Desc1)
        Desc1 = str(Desc1)
        client.send(Desc1.encode('ascii'))#bytes([Desc1])
        print('El valor del descriptor es: ')
        print(Desc1)
    else:
        print('High Density Chosen with NN:'+str(nn))
        model_perf = model_High.predict(hf)
        #model_perf
        m=model_perf.as_data_frame().values
        Desc1 = m[0][0]
        Desc1 = int(Desc1)
        #Desc1 = np.argmax(Desc1,axis=-1)
        Desc1 = str(Desc1)
        client.send(Desc1.encode('ascii'))#bytes([Desc1])
        print('El valor del descriptor es: ')
        print(Desc1)
client.close()
server.close()

