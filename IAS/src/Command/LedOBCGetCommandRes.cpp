#include "LedOBCGetCommandRes.h"
#include "Operators.h"

LedOBCGetCommandRes::LedOBCGetCommandRes(bool ledStatus)
{
    m_payload << quint8(ledStatus);
}

CommandCode LedOBCGetCommandRes::getCommandCode()
{
    return CommandCode::LED_OBC_GET_RES;
}
