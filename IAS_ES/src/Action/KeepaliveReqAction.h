#ifndef KEEPALIVEREQACTION_H
#define KEEPALIVEREQACTION_H

#include "Action.h"
#include "CommLinkMonitor.h"
#include "TransmissionQueue.h"
#include "ImageDataBase.h"

class KeepaliveReqAction : public Action
{
private:
    TransmissionQueue *m_transmissionQueue;
    ImageDataBase *m_imageDataBase;

public:
    KeepaliveReqAction(TransmissionQueue *transmissionQueue, ImageDataBase *imageDB);
    void execute(void) override;
};

#endif // KEEPALIVEREQACTION_H
