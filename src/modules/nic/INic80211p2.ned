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

package ca_system.modules.nic;

moduleinterface INic80211p2
{
    @display("i=block/ifcard");
    gates:
        input upperLayerIn2; // to upper layers
        output upperLayerOut2; // from upper layers
        output upperControlOut2; // control information
        input upperControlIn2; // control information
        input radioIn2; // radioIn gate for sendDirect
}
