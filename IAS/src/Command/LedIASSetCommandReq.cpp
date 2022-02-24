#include "LedIASSetCommandReq.h"
#include "Operators.h"

LedIASSetCommandReq::LedIASSetCommandReq(bool status)
    : m_status(status)
{
    m_payload << quint8(m_status);
}

CommandCode LedIASSetCommandReq::getCommandCode()
{
    return CommandCode::LED_IAS_SET_REQ;
}
