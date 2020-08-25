import sys
import numpy as np

Pathresults= "/home/ayanez/CA_System/src/networks/MoST_Scenario/results/"
namePrefix = "Ped_Crossing-"

#Conf = "MovinPed-S11-"
#Conf = "BL-Obstacle-S11-"
#Conf = "OnStreet-S11-"
#Conf = "MultipleTx-S11-"
Conf = "BL-NoObstacle-S11-"

#Ped_Crossing-BL-Obstacle-S11-DEN=xmldoc(#22MoST#_ped3.launchd.xml#22),290s,310s,BL=0.1s-#0.sca
#Ped_Crossing-BL-Obstacle-S11-DEN=xmldoc(#22MoST#_ped4.launchd.xml#22),130s,150s,BL=0.1s-#0.sca

DEN = ["DEN=xmldoc(#22MoST#_ped4.launchd.xml#22),130s,150s,BL=","DEN=xmldoc(#22MoST#_ped3.launchd.xml#22),290s,310s,BL="]


namePrefix = "Ped_Crossing-"
Allconf = ["MovinPed-S11-"]  #["BL-Obstacle-S11-","OnStreet-S11-",

Interval = ["0.1s"] #["1s","0.5s","0.2s",

for l in range(0,2):
	for Conf in Allconf:

		name= Pathresults + namePrefix + Conf + DEN[l] + Interval[0] + "-#" + str(i) + ".sca" #  "BL="+ Interval[k]+"," + Interval[k]+","+ Interval[k]+"," + Interval[k]  +"-#" + str(i) + ".sca" #DEN[l] + "BL="+ Interval[k] + END[l]  +"-#" + str(i) + ".sca" 

		PPM=[[],[],[],[]]

		f = open(name, 'r')
		temp = f.readlines()
		j=0

		while j<len(temp):
			if "generatedWSMs" in temp[j]:
				value = temp[j+25].split()
				Sta_T = float(value[3])

				value1 = temp[j+27].split()
				Sto_T = float(value1[3])

				value5 = temp[j+26].split()
				Total_T = float(value5[3])

				#value2 = temp[j+15].split() 
				#PKT_send = float(value2[3])
				
				value3 = temp[j+6].split()
				TimesInRules = float(value3[3])
				
				if "Bikenode" in str(value3[1]):
					Nodo = 1
				elif "Bicyclenode" in str(value3[1]):
					Nodo = 2
				elif "Pednode" in str(value3[1]):
					Nodo = 3
				else:
					Nodo = 4 

				PPM[0].append(Sta_T)
				PPM[1].append(Sto_T)
				PPM[2].append(Nodo)
				PPM[3].append(TimesInRules)
			j=j+1							

		f.close()			

		#All_PPM.append(PPM)

		out="TxNodes-"+ Conf + "V0-DEN-" + str(l)
		nameOut = out+".txt" 
		fw = open(nameOut, 'w')
				 
		for j in PPM: 
			fw.write(str(j))
			fw.write("\n")

		fw.close()	



Conf = "MultipleTx-S11-"

for l in range(0,2):

	name= Pathresults + namePrefix + Conf + DEN[l] + "-#" + str(i) + ".sca" # 
	#name= Pathresults + namePrefix + Conf +"#0.sca" # + str(i) + ".sca" 
	PPM=[[],[],[],[]]


	f = open(name, 'r')
	temp = f.readlines()
	j=0

	while j<len(temp):
		if "generatedWSMs" in temp[j]:
			value = temp[j+25].split()
			Sta_T = float(value[3])

			value1 = temp[j+27].split()
			Sto_T = float(value1[3])

			value5 = temp[j+26].split()
			Total_T = float(value5[3])

			#value2 = temp[j+15].split() 
			#PKT_send = float(value2[3])
				
			value3 = temp[j+6].split()
			TimesInRules = float(value3[3])
			
			if "Bikenode" in str(value3[1]):
				Nodo = 1
			elif "Bicyclenode" in str(value3[1]):
				Nodo = 2
			elif "Pednode" in str(value3[1]):
				Nodo = 3
			else:
				Nodo = 4 

			PPM[0].append(Sta_T)
			PPM[1].append(Sto_T)
			PPM[2].append(Nodo)
			PPM[3].append(TimesInRules)
		j=j+1							

	f.close()			

	#All_PPM.append(PPM)

	out="TxNodes-"+ Conf + "V0-DEN-" + str(l)
	nameOut = out+".txt" 
	fw = open(nameOut, 'w')
			 
	for j in PPM: 
		fw.write(str(j))
		fw.write("\n")

	fw.close()	

