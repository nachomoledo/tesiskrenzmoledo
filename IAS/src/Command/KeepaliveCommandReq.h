#ifndef KEEPALIVECOMMANDREQ_H
#define KEEPALIVECOMMANDREQ_H

#include "Command.h"

class KeepaliveCommandReq : public Command
{
public:
    KeepaliveCommandReq();
    CommandCode getCommandCode(void) override;
};

#endif // KEEPALIVECOMMANDREQ_H
