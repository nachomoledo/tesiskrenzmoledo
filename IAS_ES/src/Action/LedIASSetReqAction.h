#ifndef LEDIASSETREQACTION_H
#define LEDIASSETREQACTION_H

#include "Action.h"
#include "ImageAcquisitionSystem.h"

class LedIASSetReqAction : public Action
{
private:
    ImageAcquisitionSystem *m_ias;
    bool m_newLedStatus;
public:
    LedIASSetReqAction(ImageAcquisitionSystem *ias, bool newLedStatus);
    void execute(void) override;
};

#endif // LEDIASSETREQACTION_H
