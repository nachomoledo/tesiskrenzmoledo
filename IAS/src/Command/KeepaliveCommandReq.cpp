#include "KeepaliveCommandReq.h"
#include "Operators.h"

KeepaliveCommandReq::KeepaliveCommandReq()
{

}

CommandCode KeepaliveCommandReq::getCommandCode()
{
    return CommandCode::KEEPALIVE_REQ;
}
