//
// Copyright (C) 2008 Christoph Sommer <christoph.sommer@informatik.uni-erlangen.de>
//
// Documentation for these modules is at http://veins.car2x.org/
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

package ca_system.nodes;

import org.car2x.veins.base.modules.*;
import ca_system.modules.nic.Nic80211p;
import org.car2x.veins.modules.nic.INic80211p;


module Car
{
    parameters:
        string applType; //type of the application layer
        string nicType = default("Nic80211p"); // type of network interface card
        string veinsmobilityType = default("org.car2x.veins.modules.mobility.traci.TraCIMobility"); //type of the mobility module
		int numRadios = default(1);
		
        //Señal para guardar CBR
        @signal[MyCBR](type="double");
        @statistic[MyCBR](title="Calculo de Channel Busy Ratio"; source="MyCBR"; record=vector,stats; interpolationmode=none);

		//Señal para guardar My Collisions
        @signal[MyCollisions](type="long");
        @statistic[MyCollisions](title="Collision estimator from backoff"; source="MyColl"; record=vector,stats; interpolationmode=none);
        @display("bgb=307,273");
    gates:
        input veinsradioIn[numRadios] @directIn; // gate for sendDirect
    submodules:
        appl: <applType> like org.car2x.veins.base.modules.IBaseApplLayer {
            parameters:
                @display("p=60,50");
        }

        nic[numRadios]: <nicType> like org.car2x.veins.modules.nic.INic80211p {
            parameters:
                @display("p=60,166");
        }

        veinsmobility: <veinsmobilityType> like org.car2x.veins.base.modules.IMobility {
            parameters:
                @display("p=130,172;i=block/cogwheel");
        }

    connections:
        
        for i=0..numRadios-1 {
        nic[i].upperLayerOut --> appl.lowerLayerIn;
        nic[i].upperLayerIn <-- appl.lowerLayerOut;
        nic[i].upperControlOut --> appl.lowerControlIn;
        nic[i].upperControlIn <-- appl.lowerControlOut;
        
        veinsradioIn[i] --> nic[i].radioIn;
        }
}
