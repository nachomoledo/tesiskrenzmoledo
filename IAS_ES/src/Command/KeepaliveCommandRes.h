#ifndef KEEPALIVECOMMANDRES_H
#define KEEPALIVECOMMANDRES_H

#include "Command.h"

class KeepaliveCommandRes : public Command
{
public:
    KeepaliveCommandRes(QByteArray catalogCheckSum);
    CommandCode getCommandCode(void) override;
};

#endif // KEEPALIVECOMMANDRES_H
