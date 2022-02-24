#ifndef LEDIASGETREQACTION_H
#define LEDIASGETREQACTION_H

#include "Action.h"
#include "ImageAcquisitionSystem.h"
#include "TransmissionQueue.h"

class LedIASGetReqAction : public Action
{
private:
    ImageAcquisitionSystem *m_ias;
    TransmissionQueue *m_transmissionQueue;

public:
    LedIASGetReqAction(ImageAcquisitionSystem *ias, TransmissionQueue *transmissionQueue);
    void execute(void) override;
};

#endif // LEDIASGETREQACTION_H
