import sys
import numpy as np

# S4 n1

PPM =[[],[],[]] # Ti,Tf, nodo
List1 = [[],[]] #PDR - CBR

#Ped_Crossing-BL-NoObstacle-DEN=23500s,BL=1s,1s,1s,1s,23510s-#0.sca [22406 22409] [22537 22540] [22887 22890] [23506 23509]
name="/home/ayanez/CA_System/src/networks/MoST_Scenario/results/Ped_Crossing-BL-NoObstacle-S4-DEN=20599s,BL=1s,1s,1s,1s,20602s-#0.sca" #/home/ayanez/CA_System/src/networks/MoST_Scenario/results/Ped_Crossing-BL-WithObstacle-200bytes-S3-#0.sca" #Ped_Crossing-BL-NoObstacle-DEN=23500s,BL=1s,1s,1s,1s,23510s-#0.sca" #
#CBR =[];
f = open(name, 'r')
temp = f.readlines()
j=0

while j<len(temp):
    if "generatedWSMs" in temp[j]:
        value = temp[j+24].split()
        Sta_T = float(value[3])

        value1 = temp[j+26].split()
        Sto_T = float(value1[3])

        value5 = temp[j+25].split()
        Total_T = float(value5[3])

        value2 = temp[j+17].split()
        PKT_Lost = float(value2[3])

        value3 = temp[j+3].split()
        PKT_Rec = float(value3[3])

        value4 = temp[j+23].split()
        Busy_T = float(value4[3])
        #CBR.append(SenNumber)
#MoST_scenario.Bikenode[17].nic.mac1609_4
#value5 = temp[j+23].split()
        if "Bikenode" in str(value4[1]):
            Nodo = 1
        elif "Bicyclenode" in str(value4[1]):
            Nodo = 2
        elif "Pednode" in str(value4[1]):
            Nodo = 3
        else:
            Nodo = 4 

        delta_t=Sto_T-Sta_T
        if 1>0 :

            PPM[0].append(Sta_T)
            PPM[1].append(Sto_T)
            PPM[2].append(Nodo)

            #PDR = 1-(PKT_Lost/(PKT_Rec+PKT_Lost))
#            CBR = Busy_T/Total_T
#            List1[0].append(PDR)
#            List1[1].append(CBR)
    j=j+1							

f.close()			
		
#out = "MeanMetrics-BL"
out = "MeanMetrics-NoObstacle-S4-d1"
#out = "MeanMetrics-MultipleTx"
#out = "MeanMetrics-OnStreet"


#print("MeanRuns PDR: "+ str(MeanRunsPDR))

nameOut = out+".txt" 
fw = open(nameOut, 'w')
 
for line in PPM:
    fw.write(str(line))
    fw.write("\n")
fw.close()	


PPM =[[],[],[]] # Ti,Tf, nodo
List1 = [[],[]] #PDR - CBR

#Ped_Crossing-BL-NoObstacle-DEN=23500s,BL=1s,1s,1s,1s,23510s-#0.sca [22406 22409] [22537 22540] [22887 22890] [23506 23509]
name="/home/ayanez/CA_System/src/networks/MoST_Scenario/results/Ped_Crossing-BL-NoObstacle-S4-DEN=22330s,BL=1s,1s,1s,1s,22333s-#0.sca" #/home/ayanez/CA_System/src/networks/MoST_Scenario/results/Ped_Crossing-BL-WithObstacle-200bytes-S3-#0.sca" #Ped_Crossing-BL-NoObstacle-DEN=23500s,BL=1s,1s,1s,1s,23510s-#0.sca" #

#CBR =[];w
f = open(name, 'r')
temp = f.readlines()
j=0

while j<len(temp):
    if "generatedWSMs" in temp[j]:
        value = temp[j+24].split()
        Sta_T = float(value[3])

        value1 = temp[j+26].split()
        Sto_T = float(value1[3])

        value5 = temp[j+25].split()
        Total_T = float(value5[3])

        value2 = temp[j+17].split()
        PKT_Lost = float(value2[3])

        value3 = temp[j+3].split()
        PKT_Rec = float(value3[3])

        value4 = temp[j+23].split()
        Busy_T = float(value4[3])
        #CBR.append(SenNumber)
#MoST_scenario.Bikenode[17].nic.mac1609_4
#value5 = temp[j+23].split()
        if "Bikenode" in str(value4[1]):
            Nodo = 1
        elif "Bicyclenode" in str(value4[1]):
            Nodo = 2
        elif "Pednode" in str(value4[1]):
            Nodo = 3
        else:
            Nodo = 4 

        delta_t=Sto_T-Sta_T
        if 1>0 :

            PPM[0].append(Sta_T)
            PPM[1].append(Sto_T)
            PPM[2].append(Nodo)

            #PDR = 1-(PKT_Lost/(PKT_Rec+PKT_Lost))
#            CBR = Busy_T/Total_T
#            List1[0].append(PDR)
#            List1[1].append(CBR)
    j=j+1							

f.close()			
		
#out = "MeanMetrics-BL"
out = "MeanMetrics-NoObstacle-S4-d2"
#out = "MeanMetrics-MultipleTx"
#out = "MeanMetrics-OnStreet"


#print("MeanRuns PDR: "+ str(MeanRunsPDR))

nameOut = out+".txt" 
fw = open(nameOut, 'w')
 
for line in PPM:
    fw.write(str(line))
    fw.write("\n")
fw.close()	


PPM =[[],[],[]] # Ti,Tf, nodo
List1 = [[],[]] #PDR - CBR

#Ped_Crossing-BL-NoObstacle-DEN=23500s,BL=1s,1s,1s,1s,23510s-#0.sca               [22406 22409] [22537 22540] [22887 22890] [23506 23509] 20599s,22330s,22881s,23016s
name="/home/ayanez/CA_System/src/networks/MoST_Scenario/results/Ped_Crossing-BL-NoObstacle-S4-DEN=22113s,BL=1s,1s,1s,1s,22116s-#0.sca" #/home/ayanez/CA_System/src/networks/MoST_Scenario/results/Ped_Crossing-BL-WithObstacle-200bytes-S3-#0.sca" #Ped_Crossing-BL-NoObstacle-DEN=23500s,BL=1s,1s,1s,1s,23510s-#0.sca" #

#CBR =[];
f = open(name, 'r')
temp = f.readlines()
j=0

while j<len(temp):
    if "generatedWSMs" in temp[j]:
        value = temp[j+24].split()
        Sta_T = float(value[3])

        value1 = temp[j+26].split()
        Sto_T = float(value1[3])

        value5 = temp[j+25].split()
        Total_T = float(value5[3])

        value2 = temp[j+17].split()
        PKT_Lost = float(value2[3])

        value3 = temp[j+3].split()
        PKT_Rec = float(value3[3])

        value4 = temp[j+23].split()
        Busy_T = float(value4[3])
        #CBR.append(SenNumber)
#MoST_scenario.Bikenode[17].nic.mac1609_4
#value5 = temp[j+23].split()
        if "Bikenode" in str(value4[1]):
            Nodo = 1
        elif "Bicyclenode" in str(value4[1]):
            Nodo = 2
        elif "Pednode" in str(value4[1]):
            Nodo = 3
        else:
            Nodo = 4 

        delta_t=Sto_T-Sta_T
        if 1>0 :

            PPM[0].append(Sta_T)
            PPM[1].append(Sto_T)
            PPM[2].append(Nodo)

            #PDR = 1-(PKT_Lost/(PKT_Rec+PKT_Lost))
#            CBR = Busy_T/Total_T
#            List1[0].append(PDR)
#            List1[1].append(CBR)
    j=j+1							

f.close()			
		
#out = "MeanMetrics-BL"
out = "MeanMetrics-NoObstacle-S4-d3"
#out = "MeanMetrics-MultipleTx"
#out = "MeanMetrics-OnStreet"


#print("MeanRuns PDR: "+ str(MeanRunsPDR))

nameOut = out+".txt" 
fw = open(nameOut, 'w')
 
for line in PPM:
    fw.write(str(line))
    fw.write("\n")
fw.close()	

PPM =[[],[],[]] # Ti,Tf, nodo
List1 = [[],[]] #PDR - CBR

#Ped_Crossing-BL-NoObstacle-DEN=23500s,BL=1s,1s,1s,1s,23510s-#0.sca [22406 22409] [22537 22540] [22887 22890] [23056 23059] 23016s 21997s,22113s
name="/home/ayanez/CA_System/src/networks/MoST_Scenario/results/Ped_Crossing-BL-NoObstacle-S4-DEN=23916s,BL=1s,1s,1s,1s,23919s-#0.sca" #/home/ayanez/CA_System/src/networks/MoST_Scenario/results/Ped_Crossing-BL-WithObstacle-200bytes-S3-#0.sca" #Ped_Crossing-BL-NoObstacle-DEN=23500s,BL=1s,1s,1s,1s,23510s-#0.sca" #

#CBR =[];
f = open(name, 'r')
temp = f.readlines()
j=0

while j<len(temp):
    if "generatedWSMs" in temp[j]:
        value = temp[j+24].split()
        Sta_T = float(value[3])

        value1 = temp[j+26].split()
        Sto_T = float(value1[3])

        value5 = temp[j+25].split()
        Total_T = float(value5[3])

        value2 = temp[j+17].split()
        PKT_Lost = float(value2[3])

        value3 = temp[j+3].split()
        PKT_Rec = float(value3[3])

        value4 = temp[j+23].split()
        Busy_T = float(value4[3])
        #CBR.append(SenNumber)
#MoST_scenario.Bikenode[17].nic.mac1609_4
#value5 = temp[j+23].split()
        if "Bikenode" in str(value4[1]):
            Nodo = 1
        elif "Bicyclenode" in str(value4[1]):
            Nodo = 2
        elif "Pednode" in str(value4[1]):
            Nodo = 3
        else:
            Nodo = 4 

        delta_t=Sto_T-Sta_T
        if 1>0 :

            PPM[0].append(Sta_T)
            PPM[1].append(Sto_T)
            PPM[2].append(Nodo)

            #PDR = 1-(PKT_Lost/(PKT_Rec+PKT_Lost))
#            CBR = Busy_T/Total_T
#            List1[0].append(PDR)
#            List1[1].append(CBR)
    j=j+1							

f.close()			
		
#out = "MeanMetrics-BL"
out = "MeanMetrics-NoObstacle-S4-d4"
#out = "MeanMetrics-MultipleTx"
#out = "MeanMetrics-OnStreet"


#print("MeanRuns PDR: "+ str(MeanRunsPDR))

nameOut = out+".txt" 
fw = open(nameOut, 'w')
 
for line in PPM:
    fw.write(str(line))
    fw.write("\n")
fw.close()	

