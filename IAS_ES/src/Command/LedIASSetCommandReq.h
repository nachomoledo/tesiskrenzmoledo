#ifndef LEDIASSETCOMMANDREQ_H
#define LEDIASSETCOMMANDREQ_H

#include "Command.h"

class LedIASSetCommandReq : public Command
{
private:
    bool m_status;
public:
    LedIASSetCommandReq(bool status);
    CommandCode getCommandCode(void) override;
};

#endif // LEDIASSETCOMMANDREQ_H
