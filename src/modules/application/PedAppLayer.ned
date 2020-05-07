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

import ca_system.modules.application.ieee80211p.BaseWaveApplLayer;
//
// network description file for your Veins Application. Add parameters here
//
simple PedAppLayer extends BaseWaveApplLayer
{
    @class(PedAppLayer);
    string appName = default("My Veins App for pedestrian");
         
    //Slotted-1-persistant
    bool Slotted1 = default(false); 
    double Slotted_Ns= default(0);
    double Slotted_R= default(0);
    double Slotted_tau= default(0); 
    
    //TraD
    bool TrAD = default(false); 
    double TrAD_ti= default(0);
    double TrAD_alpha= default(0);
    double TrAD_Neig= default(0); 
    double TrAD_R= default(0); 
    
    //DSP
    bool DSP = default(false); 
    double tauDSP = default(0.000039s) @unit(s); //Author suggest 2*SIFS
    double thetaDSP = default(0s) @unit(s);
    
    //Accident
    bool MeInAcc= default(false);
    double Accident_start= default(0);
    
    //WSM periodico
    bool Send_Per_WSM = default(false);
    double wsmInterval =  default(1s) @unit(s);
    
    //MovinPed
    bool MovinPed = default(false);

    //Multiple Tx Rates
    bool MultipleTx = default(false);

    //On-StreetPed
    bool OnStreet = default(false);
    
   // double CBRInterval = default(1s) @unit(s);
}

