from datasetAutopista import beacons
from math import floor
from copy import deepcopy as copy
import random

#beacon = [speed, accel, Ptx, beaconInterval, l50, l100, l150, l200, g200]
data = []
training = []

def speedRange(x):
    if x < 2.77:
        return 0
    elif x < 5.55:
        return 1
    elif x < 8.33:
        return 2
    elif x < 11.11:
        return 3
    elif x < 13.88:
        return 4
    elif x < 16.66:
        return 5
    elif x < 19.44:
        return 6
    elif x < 22.22:
        return 7
    elif x < 25:
        return 8
    else:
        return 9

def accelRange(x):
    if x < -2:
        return 0
    elif x < -1.5:
        return 1
    elif x < -1:
        return 2
    elif x < -0.5:
        return 3
    elif x < 0:
        return 4
    elif x < 0.5:
        return 5
    else:
        return 6

def beaconIntervalRange(x):
    if x < 3:
        return 0
    elif x < 6:
        return 1
    elif x < 9:
        return 2
    elif x < 12:
        return 3
    elif x < 15:
        return 4
    elif x < 18:
        return 5
    else:
        return 6

# Fase 1: Reducir los datos con la funcion piso para disminuir la cantidad de
# diferentes valores a los atributos (ej. 4.5 = 4, 5.7 = 5, 3.2 = 3) en las
# columnas 1, 2 y 3. La columna 4 se categoriza por cada 0.5 cm (ver funcion getCategory).
for beacon in beacons:
    #beacon = [speed, accel, Ptx, beaconInterval, l50, l100, l150, l200, g200]
    #b = [speedR, accelR, beaIntR, l50, l100, l150, l200, g200, Ptx]
    b = []
    b.append(speedRange(beacon[0]))
    b.append(accelRange(beacon[1]))
    b.append(beaconIntervalRange(beacon[3]))
    b.append(beacon[4])
    b.append(beacon[5])
    b.append(beacon[6])
    b.append(beacon[7])
    b.append(beacon[8])
    b.append(beacon[2])
    data.append(b)

# Fase 2: Mezclar los datos y separar muestras para entrenamiento y prueba (80 - 20).
# Como se va a probar directamente, se copian todos los datos.
# A los datos de prueba se les separan las etiquetas para hacer la comprobacion despues.
random.shuffle(data)
for x in data:
    training.append(copy(x))

# Fase 3. Calcular las probabilidades de cada clase y de cada atributo dada la clase
# de acuerdo a los datos de entrenamiento.
def P(c, v, j=None):
    n = 0
    if not j:
        for x in training:
            if x[c] == v:
                n += 1
        return n, len(training)
    else:
        for x in training:
            if x[4] == j and x[c] == v:
                n += 1
        return n, P(4, j)[0]

print('\nProbability')
# P(c)
P10 = P(8, 10)
P20 = P(8, 20)
P30 = P(8, 30)
P40 = P(8, 40)
P50 = P(8, 50)
P60 = P(8, 60)
P70 = P(8, 70)
P80 = P(8, 80)
P90 = P(8, 90)
P100 = P(8, 100)
print(f'P(10) = {P10[0]}/{P10[1]}')
print(f'P(20) = {P20[0]}/{P20[1]}')
print(f'P(30) = {P30[0]}/{P30[1]}')
print(f'P(40) = {P40[0]}/{P40[1]}')
print(f'P(50) = {P50[0]}/{P50[1]}')
print(f'P(60) = {P60[0]}/{P60[1]}')
print(f'P(70) = {P70[0]}/{P70[1]}')
print(f'P(80) = {P80[0]}/{P80[1]}')
print(f'P(90) = {P90[0]}/{P90[1]}')
print(f'P(100) = {P100[0]}/{P100[1]}')
# P(x|c)
P5C = {0:{}, 1:{}, 2:{}, 3:{}, 4:{}, 5:{}, 6:{}, 7:{}}
P25C = {0:{}, 1:{}, 2:{}, 3:{}, 4:{}, 5:{}, 6:{}, 7:{}}
P45C = {0:{}, 1:{}, 2:{}, 3:{}, 4:{}, 5:{}, 6:{}, 7:{}}
P65C = {0:{}, 1:{}, 2:{}, 3:{}, 4:{}, 5:{}, 6:{}, 7:{}}
P85C = {0:{}, 1:{}, 2:{}, 3:{}, 4:{}, 5:{}, 6:{}, 7:{}}
P100C = {0:{}, 1:{}, 2:{}, 3:{}, 4:{}, 5:{}, 6:{}, 7:{}}
for el in training:
    for i in range(len(el)-1):
        if el[8] == 5:
            P5C[i].setdefault(el[i], 0)
            P5C[i][el[i]] += 1
        elif el[8] == 25:
            P25C[i].setdefault(el[i], 0)
            P25C[i][el[i]] += 1
        elif el[8] == 45:
            P45C[i].setdefault(el[i], 0)
            P45C[i][el[i]] += 1
        elif el[8] == 65:
            P65C[i].setdefault(el[i], 0)
            P65C[i][el[i]] += 1
        elif el[8] == 85:
            P85C[i].setdefault(el[i], 0)
            P85C[i][el[i]] += 1
        elif el[8] == 100:
            P100C[i].setdefault(el[i], 0)
            P100C[i][el[i]] += 1
# print P5C
# print P25C
# print P45C
# print P65C
# print P85C
# print P100C

# Fase 4. Probar el clasificador con los datos de prueba.
def prod(ls):
    x = 1
    for el in ls:
        x = x * el
    return x

import socket
from math import floor
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server.bind(('127.0.0.1', 6670))
server.listen(1)
while True:
    client, clientAddress = server.accept()
    req = client.recv(150)
    speed, accel, bi, l50, l100, l150, l200, g200 = req.split()
    if float(bi) == 0:
        bi = 1
    else:
        bi = floor(1/float(bi))
    caso = [float(speed), float(accel), bi, int(l50), int(l100), int(l150), int(l200), int(g200)]
    px5 = [P5C[0].setdefault(caso[0], 0), P5C[1].setdefault(caso[1], 0), P5C[2].setdefault(caso[2], 0), P5C[3].setdefault(caso[3], 0), P5C[4].setdefault(caso[4], 0), P5C[5].setdefault(caso[5], 0), P5C[6].setdefault(caso[6], 0), P5C[7].setdefault(caso[7], 0)]
    if 0 in px5:
        for i in range(len(px5)):
            px5[i] += 1
        px5 = [float(x)/(P5[1]+1) for x in px5]
        px5.append(float(P5[0]+1)/(P5[1]+1))
    else:
        px5 = [float(x)/P5[1] for x in px5]
        px5.append(float(P5[0])/P5[1])
    px5 = prod(px5)
    px25 = [P25C[0].setdefault(caso[0], 0), P25C[1].setdefault(caso[1], 0), P25C[2].setdefault(caso[2], 0), P25C[3].setdefault(caso[3], 0), P25C[4].setdefault(caso[4], 0), P25C[5].setdefault(caso[5], 0), P25C[6].setdefault(caso[6], 0), P25C[7].setdefault(caso[7], 0)]
    if 0 in px25:
        for i in range(len(px25)):
            px25[i] += 1
        px25 = [float(x)/(P25[1]+1) for x in px25]
        px25.append(float(P25[0]+1)/(P25[1]+1))
    else:
        px25 = [float(x)/P25[1] for x in px25]
        px25.append(float(P25[0])/P25[1])
    px25 = prod(px25)
    px45 = [P45C[0].setdefault(caso[0], 0), P45C[1].setdefault(caso[1], 0), P45C[2].setdefault(caso[2], 0), P45C[3].setdefault(caso[3], 0), P45C[4].setdefault(caso[4], 0), P45C[5].setdefault(caso[5], 0), P45C[6].setdefault(caso[6], 0), P45C[7].setdefault(caso[7], 0)]
    if 0 in px45:
        for i in range(len(px45)):
            px45[i] += 1
        px45 = [float(x)/(P45[1]+1) for x in px45]
        px45.append(float(P45[0]+1)/(P45[1]+1))
    else:
        px45 = [float(x)/P45[1] for x in px45]
        px45.append(float(P45[0])/P45[1])
    px45 = prod(px45)
    px65 = [P65C[0].setdefault(caso[0], 0), P65C[1].setdefault(caso[1], 0), P65C[2].setdefault(caso[2], 0), P65C[3].setdefault(caso[3], 0), P65C[4].setdefault(caso[4], 0), P65C[5].setdefault(caso[5], 0), P65C[6].setdefault(caso[6], 0), P65C[7].setdefault(caso[7], 0)]
    if 0 in px65:
        for i in range(len(px65)):
            px65[i] += 1
        px65 = [float(x)/(P65[1]+1) for x in px65]
        px65.append(float(P65[0]+1)/(P65[1]+1))
    else:
        px65 = [float(x)/P65[1] for x in px65]
        px65.append(float(P65[0])/P65[1])
    px65 = prod(px65)
    px85 = [P85C[0].setdefault(caso[0], 0), P85C[1].setdefault(caso[1], 0), P85C[2].setdefault(caso[2], 0), P85C[3].setdefault(caso[3], 0), P85C[4].setdefault(caso[4], 0), P85C[5].setdefault(caso[5], 0), P85C[6].setdefault(caso[6], 0), P85C[7].setdefault(caso[7], 0)]
    if 0 in px85:
        for i in range(len(px85)):
            px85[i] += 1
        px85 = [float(x)/(P85[1]+1) for x in px85]
        px85.append(float(P85[0]+1)/(P85[1]+1))
    else:
        px85 = [float(x)/P85[1] for x in px85]
        px85.append(float(P85[0])/P85[1])
    px85 = prod(px85)
    px100 = [P100C[0].setdefault(caso[0], 0), P100C[1].setdefault(caso[1], 0), P100C[2].setdefault(caso[2], 0), P100C[3].setdefault(caso[3], 0), P100C[4].setdefault(caso[4], 0), P100C[5].setdefault(caso[5], 0), P100C[6].setdefault(caso[6], 0), P100C[7].setdefault(caso[7], 0)]
    if 0 in px100:
        for i in range(len(px100)):
            px100[i] += 1
        px100 = [float(x)/(P100[1]+1) for x in px100]
        px100.append(float(P100[0]+1)/(P100[1]+1))
    else:
        px100 = [float(x)/P100[1] for x in px100]
        px100.append(float(P100[0])/P100[1])
    px100 = prod(px100)

    Px = px5 + px25 + px45 + px65 + px85 + px100
    px5 = px5 / Px
    px25 = px25 / Px
    px45 = px45 / Px
    px65 = px65 / Px
    px85 = px85 / Px
    px100 = px100 / Px
    Ptx = [5, 25, 45, 65, 85, 100][[px5, px25, px45, px65, px85, px100].index(max([px5, px25, px45, px65, px85, px100]))]
    client.send(str(Ptx))
    if Ptx != 100:
        print Ptx
print '[*] Clossing connection...'
client.close()
server.close()