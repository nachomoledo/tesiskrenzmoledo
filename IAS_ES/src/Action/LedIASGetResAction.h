#ifndef LEDIASGETRESACTION_H
#define LEDIASGETRESACTION_H

#include "Action.h"
#include "EarthStation.h"

class LedIASGetResAction : public Action
{
private:
    EarthStation *m_earthStation;
    bool m_stateToSet;
public:
    LedIASGetResAction(EarthStation *earthStation, bool stateToSet);
    void execute(void) override;
};

#endif // LEDIASGETRESACTION_H
