#ifndef IMAGELQREQACTION_H
#define IMAGELQREQACTION_H

#include "Action.h"
#include "CommLinkMonitor.h"
#include "TransmissionQueue.h"

class ImageLQReqAction : public Action
{
private:
    TransmissionQueue *m_transmissionQueue;
    unsigned short m_imageId;
    QString m_imagePath;
public:
    ImageLQReqAction(TransmissionQueue *transmissionQueue, unsigned short id, QString imagePath);
    void execute(void) override;
};

#endif // IMAGELQREQACTION_H
