#include "LedOBCGetCommandReq.h"

LedOBCGetCommandReq::LedOBCGetCommandReq()
{

}

CommandCode LedOBCGetCommandReq::getCommandCode()
{
    return CommandCode::LED_OBC_GET_REQ;
}
