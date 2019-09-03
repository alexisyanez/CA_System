/*
 * WaveAppToPhy80211pInterface.h
 *
 *  Created on: Sep 3, 2019
 *      Author: Alexis Yáñez *
 */

#ifndef WAVEAPPTOPHY80211PINTERFACE_H_
#define WAVEAPPTOPHY80211PINTERFACE_H_

/**
 * @brief
 * Interface of PhyLayer80211p exposed to Application Layer.
 * For enabling busy tone from DPS protocol
 *
 * @author Alexis Yáñez
 *
 */

class WaveAppToPhy80211pInterface {
public:
    virtual ~WaveAppToPhy80211pInterface() {};

    virtual void turnOnBT(bool state)=0;
    virtual void turnOn2BT(bool state)=0;
    virtual int listenBT()=0;


};

#endif /* MODULES_PHY_DSP_WAVEAPPTOPHY80211PINTERFACE_H_ */
