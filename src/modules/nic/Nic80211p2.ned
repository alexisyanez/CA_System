//
// Copyright (C) 2011 David Eckhoff <eckhoff@cs.fau.de>
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

package ca_system.modules.nic;

import ca_system.modules.phy.DSP.PhyLayer80211p2;
import ca_system.modules.mac.ieee80211p.Mac1609_4;

//
// This NIC implements an 802.11p network interface card.
//
// @author David Eckhoff
//
// @see BaseWaveApplLayer
// @see Mac1609_4
// @see PhyLayer80211p
//
module Nic80211p2 like INic80211p2
{
    gates:
        input upperLayerIn2; // to upper layers
        output upperLayerOut2; // from upper layers
        output upperControlOut2; // control information
        input upperControlIn2; // control information
        input radioIn2; // radioIn gate for sendDirect

    submodules:
        phy80211p2: PhyLayer80211p2 {
            @display("p=69,218;i=block/process_s");
        }

        mac1609_4: Mac1609_4 {
            @display("p=69,82");
        }

    connections:
        radioIn2 --> phy80211p2.radioIn;

        mac1609_4.lowerControlOut --> phy80211p2.upperControlIn;
        mac1609_4.lowerLayerOut --> phy80211p2.upperLayerIn;
        phy80211p2.upperLayerOut --> mac1609_4.lowerLayerIn;
        phy80211p2.upperControlOut --> mac1609_4.lowerControlIn;
        
        mac1609_4.upperControlIn <-- upperControlIn2;
        mac1609_4.upperLayerIn <-- upperLayerIn2;

        mac1609_4.upperLayerOut --> upperLayerOut2;
        mac1609_4.upperControlOut--> upperControlOut2;
}
