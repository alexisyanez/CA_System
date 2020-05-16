import sys
import numpy as np

#Create the name of the file, Ped_Crossing-BL-DEN=23500s,BL=0.1s,0.1s,0.1s,0.1s,23510s-#0.sca
#Pathresults= "/home/ayanez/CA_System/src/networks/MoST_Scenario/results/"

Pathresults= "/home/aware/git/CA_System/src/networks/MoST_Scenario/results/"
namePrefix = "Ped_Crossing-"

#Conf = "BL-DEN="
Conf = "MovinPed-DEN=" 
DEN= ["23500s,","28500s,","33500s,","38500s,"]
Interval = ["1s,","0.5s,","0.2s,","0.1s,"]
END= ["23510s","28510s","33510s","38510s"]


MeanRunsPDR = [[[],[],[],[]],[[],[],[],[]],[[],[],[],[]],[[],[],[],[]]]  # Filas Densidad de menos a mas, columnas Beconing 1,2,5 y 10 Hz
STDRunPDR = [[[],[],[],[]],[[],[],[],[]],[[],[],[],[]],[[],[],[],[]]]  # Filas Densidad de menos a mas, columnas Beconing 1,2,5 y 10 Hz
MeanRunsCBR = [[[],[],[],[]],[[],[],[],[]],[[],[],[],[]],[[],[],[],[]]] # Filas Densidad de menos a mas, columnas Beconing 1,2,5 y 10 Hz
STDRunCBR = [[[],[],[],[]],[[],[],[],[]],[[],[],[],[]],[[],[],[],[]]] # Filas Densidad de menos a mas, columnas Beconing 1,2,5 y 10 Hz

for l in range(0,4):
	for k in range(0,4):
		List1 = [[],[]] #PDR - CBR
		
		for i in range(0,10):
			
			name= Pathresults + namePrefix + Conf + DEN[l] + "BL="+ Interval[k] + Interval[k] + Interval[k] + Interval[k] + END[l]  +"-#" + str(i) + ".sca" 
		
			f = open(name, 'r')
			temp = f.readlines()    
			j=0
			while j<len(temp):
				if "generatedWSMs" in temp[j]:  
					value = temp[j+24].split()
					Sta_T = float(value[3])
					
					value1 = temp[j+26].split()	
					Sto_T = float(value1[3])
													
					value2 = temp[j+17].split() 
					PKT_Lost = float(value2[3])
					
					value3 = temp[j+3].split()
					PKT_Rec = float(value3[3]) 
					
					value4 = temp[j+23].split()
					Busy_T = float(value4[3]) 
					#print("Delay:"+ str(Del) + " Distancia:"+ str(DiS) +" Start_time:"+str(Sta_T) + " Stop_time:" + str(Sto_T))
					delta_t=Sto_T-Sta_T
					if delta_t > 0 and PKT_Rec>0:
						PDR = 1-(PKT_Lost/(PKT_Rec+PKT_Lost))
						CBR = Busy_T/delta_t
						List1[0].append(PDR)
						List1[1].append(CBR)						
				j=j+1							
			f.close()			
			
		MeanRunsPDR[l][k].append(np.mean(List1[0]))  
		STDRunPDR[l][k].append(np.std(List1[0])) 

		MeanRunsCBR[l][k].append(np.mean(List1[1]))  
		STDRunCBR [l][k].append(np.std(List1[1]))
			
#out = "MeanMetrics-BL"
out = "MeanMetrics-MovinPed"

#Imprimir datos en un archivo .txt

#MM1=np.asarray(MeanRunsPDR)
#MM2=np.asarray(MeanRunsCBR)
#MS1=np.asarray(STDRunPDR)
#MS2=np.asarray(STDRunCBR)

print("MeanRuns PDR: "+ str(MeanRunsPDR))

nameOut = out+".txt" 
fw = open(nameOut, 'w')
fw.write("Filas Densidad de menos a mas, columnas Beconing 1,2,5 y 10 Hz")
fw.write("Promedio PDR:\n")
for line in  MeanRunsPDR:
    fw.write(str(line))
    fw.write("\n")
fw.write("Promedio CBR:\n")
for line in MeanRunsCBR:
    fw.write(str(line))
    fw.write("\n")
fw.write("STD PDR:\n")
for line in  STDRunPDR:
    fw.write(str(line))
    fw.write("\n")
fw.write("STD CBR:\n")
for line in STDRunCBR:
    fw.write(str(line))
    fw.write("\n")

#np.savetxt(fw, MM1,fmt='%1.4f')
#fw.write("\n")
#fw.write("STD PDR\n")
#np.savetxt(fw, MS1,fmt='%1.4f')
#fw.write("\n")
#fw.write("Promedios CBR\n")
#np.savetxt(fw, MM2,fmt='%1.4f')
#fw.write("\n")
#fw.write("STD DS \n")
#np.savetxt(fw, MS2,fmt='%1.4f')
#fw.write("\n")
#fw.write("Numero de nodos x config\n")
#np.savetxt(fw, num )
#fw.write("/n")
fw.close()	



