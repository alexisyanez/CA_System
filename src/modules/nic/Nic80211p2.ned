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
import ca_system.modules.mac.ieee80211p.DSP.Mac1609_4_2;

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

        mac1609_4_2: Mac1609_4_2 {
            @display("p=69,82");
        }

    connections allowunconnected:
        radioIn2 --> phy80211p2.radioIn2;

        mac1609_4_2.lowerControlOut2 --> phy80211p2.upperControlIn2;
        mac1609_4_2.lowerLayerOut2 --> phy80211p2.upperLayerIn2;
        phy80211p2.upperLayerOut2 --> mac1609_4_2.lowerLayerIn2;
        phy80211p2.upperControlOut2 --> mac1609_4_2.lowerControlIn2;
        
        mac1609_4_2.upperControlIn2 <-- upperControlIn2;
        mac1609_4_2.upperLayerIn2 <-- upperLayerIn2;

        mac1609_4_2.upperLayerOut2 --> upperLayerOut2;
        mac1609_4_2.upperControlOut2--> upperControlOut2;
}
