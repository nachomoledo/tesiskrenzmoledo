#include "ActionFactoryOBC.h"
#include "LedOBCGetReqAction.h"
#include "LedOBCSetReqAction.h"
#include "PacketReader.h"

#include <QDebug>

ActionFactoryOBC::ActionFactoryOBC(OnBoardComputer *obc, TransmissionQueue *transmissionQueue)
    : ActionFactory(), m_obc(obc), m_transmissionQueue(transmissionQueue)
{
    registerCreateActionFn(static_cast<quint8>(CommandCode::LED_OBC_GET_REQ), [=](const QByteArray &packet) { return this->createLedOBCGetAction(packet);});
    registerCreateActionFn(static_cast<quint8>(CommandCode::LED_OBC_SET_REQ), [=](const QByteArray &packet) { return this->createLedOBCSetAction(packet);});
}

Action *ActionFactoryOBC::createLedOBCGetAction(const QByteArray &packet)
{
    Q_UNUSED(packet)
    return new LedOBCGetReqAction(m_obc, m_transmissionQueue);
}

Action *ActionFactoryOBC::createLedOBCSetAction(const QByteArray &packet)
{
    PacketReader packetReader(packet);
    packetReader.skip(5);
    bool ledStatus = packetReader.readUChar();
    return new LedOBCSetReqAction(m_obc, ledStatus);
}
