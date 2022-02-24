#include "LedIASGetCommandReq.h"
#include "Operators.h"

LedIASGetCommandReq::LedIASGetCommandReq()
{

}

CommandCode LedIASGetCommandReq::getCommandCode()
{
    return CommandCode::LED_IAS_GET_REQ;
}
