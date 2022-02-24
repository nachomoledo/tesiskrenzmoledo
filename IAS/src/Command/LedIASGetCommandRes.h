#ifndef LEDIASGETCOMMANDRES_H
#define LEDIASGETCOMMANDRES_H

#include "Command.h"

class LedIASGetCommandRes : public Command
{
public:
    LedIASGetCommandRes(bool ledStatus);
    CommandCode getCommandCode(void) override;
};

#endif // LEDIASGETCOMMANDRES_H
