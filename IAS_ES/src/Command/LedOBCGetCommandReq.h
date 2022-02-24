#ifndef LEDOBCGETCOMMANDREQ_H
#define LEDOBCGETCOMMANDREQ_H

#include "Command.h"

class LedOBCGetCommandReq : public Command
{
public:
    LedOBCGetCommandReq();
    CommandCode getCommandCode(void) override;
};

#endif // LEDOBCGETCOMMANDREQ_H
