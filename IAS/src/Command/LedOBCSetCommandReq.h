#ifndef LEDOBCSETCOMMANDREQ_H
#define LEDOBCSETCOMMANDREQ_H

#include "Command.h"

class LedOBCSetCommandReq : public Command
{
private:
    bool m_status;
public:
    LedOBCSetCommandReq(bool status);
    CommandCode getCommandCode(void) override;
};

#endif // LEDOBCSETCOMMANDREQ_H
