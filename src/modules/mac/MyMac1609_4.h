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

#ifndef MODULES_MAC_MYMAC1609_4_H_
#define MODULES_MAC_MYMAC1609_4_H_
#include <omnetpp.h>
#include "veins/modules/mac/ieee80211p/Mac1609_4.h"

using namespace omnetpp;

class MyMac1609_4 : public Mac1609_4 {

    public:
        MyMac1609_4();
        virtual ~MyMac1609_4();
        virtual double getCBR(simtime_t thistime,simtime_t tinterval) const;
    protected:
        /** @brief Initialization of the module and some variables.*/
        virtual void initialize(int);

        /** @brief Delete all dynamically allocated objects of the module.*/
        virtual void finish();


        double CBR;
    };

#endif /* MODULES_MAC_MYMAC1609_4_H_ */
