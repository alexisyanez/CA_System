import sys
import numpy as np


Pathresults= "/home/ayanez/CA_System/src/networks/MoST_Scenario/results/"

#Pathresults= "/home/aware/git/CA_System/src/networks/MoST_Scenario/results/"
namePrefix = "Ped_Crossing-"

#Conf = "MovinPed-S11-"
#Conf = "BL-Obstacle-S11-"
Conf = "OnStreet-S11-"
#Conf = "MultipleTx-S11-"
#Conf = "BL-NoObstacle-S11-"

#Ped_Crossing-BL-Obstacle-S11-DEN=xmldoc(#22MoST#_ped3.launchd.xml#22),290s,310s,BL=0.1s-#0.sca
#Ped_Crossing-BL-Obstacle-S11-DEN=xmldoc(#22MoST#_ped4.launchd.xml#22),130s,150s,BL=0.1s-#0.sca

DEN = ["DEN=xmldoc(#22MoST#_ped4.launchd.xml#22),130s,150s,BL=","DEN=xmldoc(#22MoST#_ped3.launchd.xml#22),290s,310s,BL="]


Interval = ["1s","0.5s","0.2s","0.1s"]

Total_Nodes = [213, 394] 
bec_freq = [1,2,5,10]

# PDR -> tomando lost packets
# PDR2 -> tomando total send pkt
# PDR3 -> tomando desired total send pkt

# CBR -> tomando TotalBusyTime/TotalNodeTime
# CBR2 -> tomando la media de la medición del CBR en 250ms

MeanRunsPDR = [[[],[],[],[]],[[],[],[],[]],[[],[],[],[]],[[],[],[],[]]]  # Filas Densidad de menos a mas, columnas Beconing 1,2,5 y 10 Hz
STDRunPDR = [[[],[],[],[]],[[],[],[],[]],[[],[],[],[]],[[],[],[],[]]]  # Filas Densidad de menos a mas, columnas Beconing 1,2,5 y 10 Hz

MeanRunsCBR = [[[],[],[],[]],[[],[],[],[]],[[],[],[],[]],[[],[],[],[]]] # Filas Densidad de menos a mas, columnas Beconing 1,2,5 y 10 Hz
STDRunCBR = [[[],[],[],[]],[[],[],[],[]],[[],[],[],[]],[[],[],[],[]]] # Filas Densidad de menos a mas, columnas Beconing 1,2,5 y 10 Hz

MeanRunsPDR2 = [[[],[],[],[]],[[],[],[],[]],[[],[],[],[]],[[],[],[],[]]]  # Filas Densidad de menos a mas, columnas Beconing 1,2,5 y 10 Hz
STDRunPDR2 = [[[],[],[],[]],[[],[],[],[]],[[],[],[],[]],[[],[],[],[]]]  # Filas Densidad de menos a mas, columnas Beconing 1,2,5 y 10 Hz

MeanRunsCBR2 = [[[],[],[],[]],[[],[],[],[]],[[],[],[],[]],[[],[],[],[]]] # Filas Densidad de menos a mas, columnas Beconing 1,2,5 y 10 Hz
STDRunCBR2 = [[[],[],[],[]],[[],[],[],[]],[[],[],[],[]],[[],[],[],[]]] # Filas Densidad de menos a mas, columnas Beconing 1,2,5 y 10 Hz

MeanRunsPDR3 = [[[],[],[],[]],[[],[],[],[]],[[],[],[],[]],[[],[],[],[]]]  # Filas Densidad de menos a mas, columnas Beconing 1,2,5 y 10 Hz
STDRunPDR3 = [[[],[],[],[]],[[],[],[],[]],[[],[],[],[]],[[],[],[],[]]]  # Filas Densidad de menos a mas, columnas Beconing 1,2,5 y 10 Hz

RealSendPkt = [[[],[],[],[]],[[],[],[],[]],[[],[],[],[]],[[],[],[],[]]] # Filas Densidad de menos a mas, columnas Beconing 1,2,5 y 10 Hz
DesiredSendPkt = [[[],[],[],[]],[[],[],[],[]],[[],[],[],[]],[[],[],[],[]]] #wFilas Densidad de menos a mas, columnas Beconing 1,2,5 y 10 Hz

for l in range(0,2):	
	for k in range(0,4):
		List1 = [[],[]] #PDR - CBR
		PDR2 = [] #New PDR
		PDR3 = []
		CBR2 = [] #CBR media
		
		Suma_Send = []
		Desired_Send = []
				
		for i in range(0,5): #(0,10):
			comp=[[],[],[]]
			PKT_Total_Rec = []
			PKT_Total_Send = []
			#List1 = [[],[]]
			name= Pathresults + namePrefix + Conf + DEN[l] + Interval[k] + "-#" + str(i) + ".sca" #  "BL="+ Interval[k]+"," + Interval[k]+","+ Interval[k]+"," + Interval[k]  +"-#" + str(i) + ".sca" #DEN[l] + "BL="+ Interval[k] + END[l]  +"-#" + str(i) + ".sca" 

			#CBR =[];
			f = open(name, 'r')
			temp = f.readlines()
			j=0
			while j<len(temp):
				if "generatedWSMs" in temp[j]:
					
					value3 = temp[j+3].split()
					PKT_Rec = float(value3[3])
					
					value6 = temp[j+7].split()
					CBR_Media = float(value6[3])

					value2 = temp[j+16].split() #15 previo CBR medio 
					PKT_send = float(value2[3])
					
					value5 = temp[j+19].split() #18 previo CBR medio 
					PKT_Lost = float(value5[3])
					
					value4 = temp[j+25].split() #24 previo CBR medio 
					Busy_T = float(value4[3])
					
					value = temp[j+26].split() #25 previo CBR medio 
					Sta_T = float(value[3])

					value5 = temp[j+27].split() #26 previo CBR medio 
					Total_T = float(value5[3])

					value1 = temp[j+28].split() #27 previo CBR medio
					Sto_T = float(value1[3])

					delta_t=Sto_T-Sta_T


					PKT_Total_Rec.append(PKT_Rec)
					PKT_Total_Send.append(PKT_send)
					if Total_T > 0:
						CBR = Busy_T/delta_t
						PDR = 1-(PKT_Lost/(PKT_Rec+PKT_Lost))
						List1[1].append(CBR)
						List1[0].append(PDR)
						
						CBR2.append(CBR_Media)

				j=j+1
			f.close()
			
			Suma_Send.append(sum(PKT_Total_Send))

			Num_Nodes = Total_Nodes[l] #[l] #sum(PKT_Total_Rec)

			Desired_Send.append(bec_freq[k]*20*Num_Nodes)

			PDR_2 = sum(PKT_Total_Rec)/(sum(PKT_Total_Send)*Num_Nodes) 
			PDR2.append(PDR_2)

			PDR_3 = sum(PKT_Total_Rec)/(bec_freq[k]*20*Num_Nodes*Num_Nodes) 
			PDR3.append(PDR_3)
		
		MeanRunsPDR[l][k].append(np.mean(List1[0]))  
		STDRunPDR[l][k].append(np.std(List1[0])) 

		MeanRunsCBR[l][k].append(np.mean(List1[1]))  
		STDRunCBR[l][k].append(np.std(List1[1]))

		DesiredSendPkt[l][k].append(np.mean(Desired_Send))
		RealSendPkt[l][k].append(np.mean(Suma_Send))

		MeanRunsPDR2[l][k].append(np.mean(PDR2))  
		STDRunPDR2[l][k].append(np.std(PDR2)) 

		MeanRunsCBR2[l][k].append(np.mean(CBR2)/0.25)  
		STDRunCBR2[l][k].append(np.std(CBR2)/0.25)
		
		MeanRunsPDR3[l][k].append(np.mean(PDR3))  
		STDRunPDR3[l][k].append(np.std(PDR3)) 

#out = "MeanMetrics-BL-Obstacle-S11"
#out = "MeanMetrics-MovinPed-S11"
out = "MeanMetrics-OnStreet-S11"
#out = "MeanMetrics-MultipleTx-S11"
#out = "MeanMetrics-BL-NoObstacle-S11"


print("MeanRuns PDR: "+ str(MeanRunsPDR))

# PDR -> tomando lost packets
# PDR2 -> tomando total send pkt
# PDR3 -> tomando desired total send pkt

# CBR -> tomando TotalBusyTime/TotalNodeTime
# CBR2 -> tomando la media de la medición del CBR en 250ms

nameOut = out+".txt" 
fw = open(nameOut, 'w')
fw.write("Filas Densidad de menos a mas, columnas Beconing 1,2,5 y 10 Hz \n Cálculo realizado con paquetes generados en la capa MAC \n")

fw.write("Promedio PDR usando LostPackets:\n")
for line in  MeanRunsPDR:
    fw.write(str(line))
    fw.write("\n")
    
fw.write("STD PDR:\n")
for line in  STDRunPDR:
    fw.write(str(line))
    fw.write("\n")
    
fw.write("Promedio CBR usando TotalBusyTime/TotalNodeTime:\n")
for line in MeanRunsCBR:
    fw.write(str(line))
    fw.write("\n")

fw.write("STD CBR:\n")
for line in STDRunCBR:
    fw.write(str(line))
    fw.write("\n")

fw.write("Promedio PDR usando Total send pkt:\n")
for line in  MeanRunsPDR2:
    fw.write(str(line))
    fw.write("\n")
    
fw.write("STD PDR:\n")
for line in  STDRunPDR2:
    fw.write(str(line))
    fw.write("\n")
    
fw.write("Promedio CBR usando la media de la medición del CBR en 250ms:\n")
for line in MeanRunsCBR2:
    fw.write(str(line))
    fw.write("\n")

fw.write("STD CBR:\n")
for line in STDRunCBR2:
    fw.write(str(line))
    fw.write("\n")

fw.write("Promedio PDR usando desired total send pkt:\n")
for line in  MeanRunsPDR3:
    fw.write(str(line))
    fw.write("\n")
    
fw.write("STD PDR:\n")
for line in  STDRunPDR3:
    fw.write(str(line))
    fw.write("\n")
   
fw.write("Número estimado real de paquetes enviados\n")
for line in RealSendPkt:
    fw.write(str(line))
    fw.write("\n")
fw.write("Número deseado de paquetes enviados\n")
for line in DesiredSendPkt:
    fw.write(str(line))
    fw.write("\n")



fw.close()
