import sys
import numpy as np

Pathresults= "/home/alexis/git/CA_System/src/networks/MoST_Scenario/results/"

namePrefix = "Ped_Crossing-"

Conf = "BL-NoObstacle-S8-DEN="

DEN= ["18000s,","19000s,", "20000s,", "21000s,", "22000s,", "23000s,", "28000s,", "29000s,", "30000s,"]
Interval = ["1s,","0.5s,","0.2s,","0.1s,"]
END= ["18010s,", "19010s,", "20010s,", "21010s,", "22010s,", "23010s," , "28010s,", "29010s,", "30010s,"]


#PPM =[[],[],[]] # Ti,Tf, nodo
List1 = [[],[]] #PDR - CBR

All_PPM = []

for l in range(0,length(DEN)):
	for k in Interval:
#name= Pathresults + namePrefix + Conf +  DEN[l] + "BL="+ Interval[k] + Interval[k] + Interval[k] + Interval[k] + END[l]  +"-#0.sca" # + str(i) + ".sca" 
		name= Pathresults + namePrefix + Conf +  DEN[l] + "BL="+ k + END[l]  +"-#0.sca" # + str(i) + ".sca" 
		PPM=[[],[],[]]

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

			j=j+1							

		f.close()			

		#All_PPM.append(PPM)

		out="Comp_All_Scenario_S8"
		nameOut = out+".txt" 
		fw = open(nameOut, 'w')
				 
		for l in All_PPM:
			for j in PPM: 
				fw.write(str(j))
				fw.write("\n")

		fw.close()	


