#ifndef ACTIONFACTORYOBC_H
#define ACTIONFACTORYOBC_H

#include "ActionFactory.h"
#include "TransmissionQueue.h"
#include "OnBoardComputer.h"

class ActionFactoryOBC : public ActionFactory
{
private:
    OnBoardComputer *m_obc;
    TransmissionQueue* m_transmissionQueue;
    Action *createLedOBCGetAction(const QByteArray &packet);
    Action *createLedOBCSetAction(const QByteArray &packet);

public:
    ActionFactoryOBC(OnBoardComputer *obc, TransmissionQueue *transmissionQueue = nullptr);
};

#endif // ACTIONFACTORYOBC_H
