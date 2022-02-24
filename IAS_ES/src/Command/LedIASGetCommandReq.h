#ifndef LEDIASGETCOMMANDREQ_H
#define LEDIASGETCOMMANDREQ_H

#include "Command.h"

class LedIASGetCommandReq : public Command
{
public:
    LedIASGetCommandReq();
    CommandCode getCommandCode(void) override;
};

#endif // LEDIASGETCOMMANDREQ_H
