#ifndef DELETECOMMANDREQ_H
#define DELETECOMMANDREQ_H

#include "Command.h"
#include <QList>

class DeleteCommandReq : public Command
{
private:
    QList<quint16> m_imageIds;

public:
    DeleteCommandReq(QList<quint16> imageIds);
    CommandCode getCommandCode(void) override;
};

#endif // DELETECOMMANDREQ_H
