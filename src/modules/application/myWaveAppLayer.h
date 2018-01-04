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

#ifndef MODULES_APPLICATION_MYWAVEAPPLAYER_H_
#define MODULES_APPLICATION_MYWAVEAPPLAYER_H_

#include <omnetpp.h>
#include "veins/modules/application/ieee80211p/BaseWaveApplLayer.h"
#include "veins/base/utils/Coord.h"
#include "veins/base/utils/FWMath.h"


using namespace omnetpp;

class myWaveAppLayer : public BaseWaveApplLayer{
    private:
        //Slotted-1-persistant
        bool Slotted1Enabled;
        double Slotted_Ns;
        double Slotted_R;
        double Slotted_tau;

    public:
        virtual void initialize(int stage);
        virtual void finish();
        double distance(const Coord& a, const Coord& b);

    protected:
        simtime_t lastDroveAt;
        bool sentMessage;
        int currentSubscribedServiceId;
    protected:
        virtual void onBSM(BasicSafetyMessage* bsm);
        virtual void onWSM(WaveShortMessage* wsm);
        virtual void onWSA(WaveServiceAdvertisment* wsa);

        virtual void handleSelfMsg(cMessage* msg);
        virtual void handlePositionUpdate(cObject* obj);

    };

#endif /* MODULES_APPLICATION_MYWAVEAPPLAYER_H_ */