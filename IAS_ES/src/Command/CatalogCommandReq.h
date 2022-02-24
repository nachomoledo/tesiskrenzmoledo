#ifndef CATALOGCOMMANDREQ_H
#define CATALOGCOMMANDREQ_H

#include "Command.h"

class CatalogCommandReq : public Command
{
public:
    CatalogCommandReq();
    CommandCode getCommandCode(void) override;
};

#endif // CATALOGCOMMANDREQ_H
