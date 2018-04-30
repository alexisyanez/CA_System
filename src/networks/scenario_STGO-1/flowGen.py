#!/usr/bin/env python
"""
@file    runner.py
@author  Lena Kalleske
@author  Daniel Krajzewicz
@author  Michael Behrisch
@date    2009-03-26
@version $Id: runner.py 14678 2013-09-11 08:53:06Z behrisch $

Route generation script.

SUMO, Simulation of Urban MObility; see http://sumo.sourceforge.net/
Copyright (C) 2009-2012 DLR/TS, Germany

This file is part of SUMO.
SUMO is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.
"""

import os, sys
import optparse
import subprocess
import random

def generate_routefile():
    random.seed(41) # make tests reproducible
    N = 2000 # number of time steps
    Nr = 20	
    # demand per second from different directions
    pBus = 1./4 		#right-down road
    #pLL = 1./11			#Left-left road
    #pDL = 1./12			#Down-low road
    #pDR = 1./30			#Down-right road
    #pDD = 1./1			#Down-down road
    with open("cross.rou.xml", "w") as routes:
        print >> routes, """<?xml version="1.0"?>
<routes>
   <vType id="typePassenger" accel="2.6" decel="4.5" sigma="0.5" length="2.5" minGap="1" maxSpeed="19" guiShape="passenger"/>
   <vType id="typeBus" accel="0.8" decel="4.5" sigma="0.5" length="10" minGap="3" maxSpeed="19" guiShape="bus"/>

   <route id="route0" edges="-39539626 -5445204#2 -5445204#1 113939244#2 -126606716 23339459 30405358#1 85355912 85355911#0 85355911#1 30405356 5931612 30350450#0 30350450#1 30350450#2 4006702#0 4006702#1 4900043 4900041#1"/>

   <route id="route1" edges="31241835#1 -31241835#1 -31241816#3 31241851#0 31241851#1 31241851#2 -31255203#0 -4006702#0 4319352#1 44069041#0 44069041#1 25472079 30405352 30350445 -33174302#1 -33174302#0 -32270595 -29900561#1 -29900561#0 -4006688#4 -4006688#3 10712013"/>

   <route id="route2" edges="-28631632 28613727#1 -94344940#0 28768072 -28613737 -4006702#0 4319352#1 44069041#0 44069041#1 25472079 30405352 30350445 -33174302#1 -33174302#0 -32270595 8402997 8402998#1 8402998#2 29900564#1 29900564#2 -29900564#2"/>

   <route id="route3" edges="-8402997 32270595 33174302#0 33174302#1 4686970#0 4686970#1 122161381 30350448 8364476 30350450#0 -3998645#2 -3998645#1"/>

   <route id="route4" edges="32302591#0 32302591#1 32302591#2 32302591#3 32302591#4 32302591#5 33174302#0 33174302#1 4686970#0 4686970#1 122161381 30350448 8364476 30350450#0 -3998645#2 -3998645#1 -4006726#2 -4006726#1 -4006726#0"/>

   <route id="route5" edges="10419402 -4006693#1 -23605595 -8403007 -29900564#1 -8402998#2 -8402998#1 -8402997 32270595 -29900565#3"/>
    
   <route id="route6" edges="-31255203#0 -4006702#0 4319352#1 44069041#0 44069041#1 25472079 30405352 30350445 -33174302#1 -33174302#0 -32302591#5 -32302591#4 -32302591#3 -32302591#2 -32302591#1 -32302591#0 -125685391"/>

   <route id="route7" edges="85355912 85355911#0 85355911#1 30405356 5931612 30350450#0 30350450#1 30350450#2 4006702#0 31255203#0 31255203#1 31241838#0"/>

   <route id="route8" edges="-4099270#0 4006726#2 -3998645#0 -3998612#0 30357194 25472299 30350448 30350449 4047309 30751813 -35842306#1 -35842306#0"/>
    
   <route id="route9" edges="-4006726#0 -3998615#0 3013106#2 4006702#0 28613737 94344941 94344940#0 67076129"/>
   
   <route id="route10" edges="31241855#1 31241853#1 -31241838#0 -31255203#1 -31255203#0 -4006702#0 4319352#1 44069041#0 25472134 30751813 -35842306#1 -35842306#0 -4900741 -4900739#2 4690348"/>

   <route id="route11" edges="-29900564#3 -29900564#2 -29900564#1 -8402998#2 -8402998#1 -8402997 32270595 33174302#0 33174302#1 4686970#0 4686970#1 122161381 30350448 8364476 30350450#0 30350450#1 30350450#2 4006702#0 4006702#1 4006702#2 -23805514#1 -23805514#0"/>
 
   <route id="route12" edges="-31241835#1 -31241816#3 31241851#0 31241851#1 31241851#2 -31255203#0 -4006702#0 4319352#1 44069041#0 44069041#1 25472079 30405352 30350445 -33174302#1 -33174302#0 -32270595 -29900561#1 -29900561#0 -4006688#4 -4006688#3 -4006688#2 -4006688#1 -4006688#0 -31401017#0 -29900567 -31401018 -4047532"/>
    
   <route id="route13" edges="-31255203#0 -4006702#0 -3013106#2 -3013106#1 -3013106#0 -10573414#1 4047378 4006724#1 4872369 -4006725#0"/>

   <route id="route14" edges="-4006691 29900565#1 29900565#2 29900565#3 33174302#0 33174302#1 4686970#0 4686970#1 122161381 30350448 8364476 30350450#0 30350450#1 30350450#2 4006702#0 4006702#1 4006702#2 -23805514#1"/>
    
   <route id="route15" edges="-4006693#1 -23605595 -8403007 -29900564#1 -8402998#2 -8402998#1 -8402997 32270595 33174302#0 33174302#1 4686970#0 4686970#1 122161381 30350448 8364476 30350450#0 30350450#1 30350450#2 4006702#0 28613737 94344941 94344940#0 94344940#2"/>

   <route id="route16" edges="4047378 4006724#1 4872369 4006725#1 -3998612#0 30357194 25472299 30350448 30350449 4400949 31982182#0 4047241 4797872 4797871 4006668 126606716 113939242#0 113939242#1 113939242#2 113939241 -37591481"/>

   <route id="route17" edges="-31777493#0 31777493#0 31777493#1 35842306#0 35842306#1 4047446#0 4047446#1 25472079 30405352 30350445 -33174302#1 -33174302#0 -32270595 -29900561#1 -29900561#0 -8403001"/>

   <route id="route18" edges="4006688#0 4006688#1 4006688#2 4006688#3 4006688#4 29900564#0 29900564#1 29900564#2 29900564#3 29900564#4"/>

   <route id="route19" edges="31241855#0 31241816#0 31241816#1 31241851#0 31241851#1 31241851#2 -31255203#0 28613737 94344941 94344940#0 -28613727#1 -28613727#0 -28613734"/>"""
        lastVeh = 0
        vehNr = 0
        for i in range(N):
            if random.uniform(0,1) < pBus:
                print >> routes, '    <vehicle id="%i" type="typeBus" route="route%i" depart="0" departPos="random"/>' % (i,random.randrange(Nr))
                vehNr += 1
                lastVeh = i
            else: 
                print >> routes, '    <vehicle id="%i" type="typePassenger" route="route%i" depart="0" departPos="random"/>' % (i,random.randrange(Nr))
                vehNr += 1
                lastVeh = i
        
	for i in range(Nr):
            if random.uniform(0,1) < pBus:		
		print >> routes, '    <flow id="flow%s" type="typeBus" route="route%s" begin="0" period="3" number="195"/>' % (i,i)	
    	    else: 
		print >> routes, '    <flow id="flow%s" type="typePassenger" route="route%s" begin="0" period="3" number="195"/>' % (i,i)	
        print >> routes, "</routes>"

# this is the main entry point of this script
if __name__ == "__main__":
    
    generate_routefile()
