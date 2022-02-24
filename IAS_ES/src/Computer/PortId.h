#ifndef PORTID_H
#define PORTID_H

enum class PortId : int {
    // ES ports
    ES_OBC_PORT,
    ES_IAS_PORT,
    // OBC ports
    OBC_ES_PORT,
    OBC_IAS_PORT,
    // IAS ports
    IAS_OBC_PORT,
    IAS_ES_PORT,
    N_PORTS
};

#endif // PORTID_H
