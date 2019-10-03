package ca_system.modules.application.ieee80211p;

// Interface for application layer modules
moduleinterface IBaseApplLayer
{
    parameters:
        int headerLength @unit("bit"); // length of the application message header (in bits)
    gates:
        input lowerLayerIn[]; // from network layer
        output lowerLayerOut[]; // to network layer
        input lowerControlIn[]; // control from network layer
        output lowerControlOut[]; // control to network layer
        
        input lowerLayerIn2 @losse; // from network layer
        output lowerLayerOut2 @loose; // to network layer
        input lowerControlIn2 @loose; // control from network layer
        output lowerControlOut2 @loose; // control to network layer
}

