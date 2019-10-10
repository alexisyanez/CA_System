package ca_system.base.modules;

// Interface for application layer modules
moduleinterface IBaseApplLayer
{
    parameters:
        int headerLength @unit("bit"); // length of the application message header (in bits)
    gates:
        
        input lowerLayerInAP[]; // from network layer
        output lowerLayerOutAP[]; // to network layer
        input lowerControlInAP[]; // control from network layer
        output lowerControlOutAP[]; // control to network layer
}

