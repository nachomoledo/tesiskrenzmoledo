#ifndef CROPCOMMANDREQ_H
#define CROPCOMMANDREQ_H

#include "Command.h"
#include "ROI.h"
#include <QString>
#include <QList>

class CropCommandReq : public Command
{
    quint16 m_imageId;
    QList<ROI> m_roiList;
public:
    CropCommandReq(quint16 id, QList<ROI> roiList);
    CommandCode getCommandCode(void) override;
    QList<ROI> getRoiList() const;
};

#endif // CROPCOMMANDREQ_H
