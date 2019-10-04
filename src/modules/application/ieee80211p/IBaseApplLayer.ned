package ca_system.modules.application.ieee80211p;

// Interface for application layer modules
moduleinterface IBaseApplLayer
{
    parameters:
        int headerLength @unit("bit"); // length of the application message header (in bits)
        //int numRadios = default(2);
    gates:
        input lowerLayerIn[2]; // from network layer
        output lowerLayerOut[2]; // to network layer
        input lowerControlIn[2]; // control from network layer
        output lowerControlOut[2]; // control to network layer
        
        input lowerLayerIn2 @losse; // from network layer
        output lowerLayerOut2 @loose; // to network layer
        input lowerControlIn2 @loose; // control from network layer
        output lowerControlOut2 @loose; // control to network layer
}

