package ca_system.modules.application.ieee80211p;

// Interface for application layer modules
moduleinterface IBaseApplLayer
{
    parameters:
        int headerLength @unit("bit"); // length of the application message header (in bits)
    gates:
        input lowerLayerIn; // from network layer
        output lowerLayerOut; // to network layer
        input lowerControlIn; // control from network layer
        output lowerControlOut; // control to network layer
        
        input lowerLayerIn2; // from network layer
        output lowerLayerOut2; // to network layer
        input lowerControlIn2; // control from network layer
        output lowerControlOut2; // control to network layer
}

