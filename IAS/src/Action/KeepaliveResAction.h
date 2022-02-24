#ifndef KEEPALIVERESACTION_H
#define KEEPALIVERESACTION_H

#include "Action.h"
#include "CommLinkMonitor.h"
#include "ImageDataBase.h"
#include "TransmissionQueue.h"

class KeepaliveResAction : public Action
{
private:
    TransmissionQueue *m_transmissionQueue;
    CommLinkMonitor *m_commLinkMonitor;
    ImageDataBase *m_imageDataBase;
    QByteArray m_catalogChecksum;
public:
    KeepaliveResAction(TransmissionQueue *transmissionQueue, CommLinkMonitor *clm, ImageDataBase *imageDataBase, QByteArray atalogChecksum);
    void execute(void) override;
};

#endif // KEEPALIVERESACTION_H
