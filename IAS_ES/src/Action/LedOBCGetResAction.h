#ifndef LEDOBCGETRESACTION_H
#define LEDOBCGETRESACTION_H

#include "Action.h"
#include "EarthStation.h"

class LedOBCGetResAction : public Action
{
private:
    EarthStation *m_earthStation;
    bool m_stateToSet;
public:
    LedOBCGetResAction(EarthStation *earthStation, bool stateToSet);
    void execute(void) override;
};

#endif // LEDOBCGETRESACTION_H
