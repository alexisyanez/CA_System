//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package ca_system.modules.application;

import org.car2x.veins.modules.application.ieee80211p.BaseWaveApplLayer;
//
// network description file for your Veins Application. Add parameters here
//
simple myWaveAppLayer extends BaseWaveApplLayer
{
    @class(myWaveAppLayer);
    string appName = default("My first Veins App");
         
    //Slotted-1-persistant
    bool Slotted1 = default(false); 
    double Slotted_Ns= default(0);
    double Slotted_R= default(0);
    double Slotted_tau= default(0); 
}

