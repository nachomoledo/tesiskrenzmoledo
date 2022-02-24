#ifndef COMMAND_H
#define COMMAND_H

#include "CommandCode.h"
#include "PortId.h"
#include <QByteArray>

// TODO: agregar propiedad serial port por el que sale
class Command
{
protected:
    QByteArray m_payload;
public:
   virtual CommandCode getCommandCode(void) = 0;
   QByteArray getPayload(void);
   virtual ~Command()= default;
};

#endif // COMMAND_H
