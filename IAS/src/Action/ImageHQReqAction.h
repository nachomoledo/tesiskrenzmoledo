#ifndef IMAGEHQREQACTION_H
#define IMAGEHQREQACTION_H

#include "Action.h"
#include "CommLinkMonitor.h"
#include "TransmissionQueue.h"

class ImageHQReqAction : public Action
{
private:
    TransmissionQueue *m_transmissionQueue;
    unsigned short m_imageId;
    QString m_imagePath;
public:
    ImageHQReqAction(TransmissionQueue *transmissionQueue, unsigned short id, QString imagePath);
    void execute(void) override;
};

#endif // IMAGEHQREQACTION_H
