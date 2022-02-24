#include "LedOBCSetCommandReq.h"
#include "Operators.h"

LedOBCSetCommandReq::LedOBCSetCommandReq(bool status)
    : m_status(status)
{
    m_payload << quint8(m_status);
}

CommandCode LedOBCSetCommandReq::getCommandCode()
{
    return CommandCode::LED_OBC_SET_REQ;
}
