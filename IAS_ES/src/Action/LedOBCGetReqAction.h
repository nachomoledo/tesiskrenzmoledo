#ifndef LEDOBCGETREQACTION_H
#define LEDOBCGETREQACTION_H

#include "Action.h"
#include "OnBoardComputer.h"

class LedOBCGetReqAction : public Action
{
private:
    OnBoardComputer *m_obc;
    TransmissionQueue *m_transmissionQueue;
public:
    LedOBCGetReqAction(OnBoardComputer *obc, TransmissionQueue *transmissionQueue);
    void execute(void) override;
};

#endif // LEDOBCGETREQACTION_H
