#ifndef LEDOBCSETREQACTION_H
#define LEDOBCSETREQACTION_H

#include "Action.h"
#include "OnBoardComputer.h"

class LedOBCSetReqAction : public Action
{
private:
    OnBoardComputer *m_obc;
    bool m_newLedStatus;
public:
    LedOBCSetReqAction(OnBoardComputer *obc, bool newLedStatus);
    void execute(void) override;
};

#endif // LEDOBCSETREQACTION_H
