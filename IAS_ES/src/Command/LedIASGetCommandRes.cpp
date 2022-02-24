#include "LedIASGetCommandRes.h"
#include "Operators.h"

LedIASGetCommandRes::LedIASGetCommandRes(bool ledStatus)
{
    m_payload << quint8(ledStatus);
}

CommandCode LedIASGetCommandRes::getCommandCode()
{
    return CommandCode::LED_IAS_GET_RES;
}
