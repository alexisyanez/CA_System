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

#include "MyMac1609_4.h"
//#include "veins/modules/mac/ieee80211p/Mac1609_4.h"

Define_Module(MyMac1609_4);

void MyMac1609_4::initialize(int stage) {
    Mac1609_4::initialize(stage);
}

void MyMac1609_4::finish() {
    Mac1609_4::finish();
    //statistics recording goes here

}

MyMac1609_4::MyMac1609_4() {
    // TODO Auto-generated constructor stub

}

MyMac1609_4::~MyMac1609_4() {
    // TODO Auto-generated destructor stub
}

double MyMac1609_4::getCBR(simtime_t start_time,simtime_t tinterval) const{
     simtime_t tbusy_ini= statsTotalBusyTime;
     double CBR = -1;
     while(simTime()<(start_time+tinterval)){}

     CBR = ((statsTotalBusyTime.dbl()-tbusy_ini.dbl())/tinterval.dbl());

     return CBR;

}
