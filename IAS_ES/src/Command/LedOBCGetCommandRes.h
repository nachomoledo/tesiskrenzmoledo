#ifndef LEDOBCGETCOMMANDRES_H
#define LEDOBCGETCOMMANDRES_H

#include "Command.h"

class LedOBCGetCommandRes : public Command
{
public:
    LedOBCGetCommandRes(bool ledStatus);
    CommandCode getCommandCode(void) override;
};

#endif // LEDOBCGETCOMMANDRES_H
