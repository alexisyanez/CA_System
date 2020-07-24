import sys
import numpy as np

Pathresults= "/home/ayanez/CA_System/src/networks/MoST_Scenario/results/"
namePrefix = "Ped_Crossing-"
Allconf = ["BL-Obstacle-S10-","OnStreet-S10-","MovinPed-S10-"] 

Interval = ["0.1s"] #["1s","0.5s","0.2s",


for Conf in Allconf:

	name= Pathresults + namePrefix + Conf + "BL="+ Interval[0]+"," + Interval[0]+","+ Interval[0]+"," + Interval[0] +"-#0.sca" # + str(i) + ".sca" 
	PPM=[[],[],[],[]]

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

			value2 = temp[j+14].split() 
			PKT_send = float(value2[3])
			
			if "Bikenode" in str(value2[1]):
				Nodo = 1
			elif "Bicyclenode" in str(value2[1]):
				Nodo = 2
			elif "Pednode" in str(value2[1]):
				Nodo = 3
			else:
				Nodo = 4 

			PPM[0].append(Sta_T)
			PPM[1].append(Sto_T)
			PPM[2].append(Nodo)
			PPM[3].append(PKT_send)
		j=j+1							

	f.close()			

	#All_PPM.append(PPM)

	out="TxNodes-"+ Conf
	nameOut = out+".txt" 
	fw = open(nameOut, 'w')
			 
	for j in PPM: 
		fw.write(str(j))
		fw.write("\n")

	fw.close()	



Conf = "MultipleTx-S10-"
name= Pathresults + namePrefix + Conf +"#0.sca" # + str(i) + ".sca" 
PPM=[[],[],[],[]]


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

		value2 = temp[j+14].split() 
		PKT_send = float(value2[3])
		
		if "Bikenode" in str(value2[1]):
			Nodo = 1
		elif "Bicyclenode" in str(value2[1]):
			Nodo = 2
		elif "Pednode" in str(value2[1]):
			Nodo = 3
		else:
			Nodo = 4 

		PPM[0].append(Sta_T)
		PPM[1].append(Sto_T)
		PPM[2].append(Nodo)
		PPM[3].append(PKT_send)
	j=j+1							

f.close()			

#All_PPM.append(PPM)

out="TxNodes-"+ Conf
nameOut = out+".txt" 
fw = open(nameOut, 'w')
		 
for j in PPM: 
	fw.write(str(j))
	fw.write("\n")

fw.close()	

