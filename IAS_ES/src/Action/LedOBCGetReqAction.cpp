#include "LedOBCGetReqAction.h"
#include "LedOBCGetCommandRes.h"
#include <QDebug>

LedOBCGetReqAction::LedOBCGetReqAction(OnBoardComputer *obc, TransmissionQueue *transmissionQueue)
    : m_obc(obc), m_transmissionQueue(transmissionQueue)
{

}

void LedOBCGetReqAction::execute()
{
    //qDebug() << "LedOBCGetReqAction::execute()";
    if (m_obc && m_transmissionQueue)
    {
        m_transmissionQueue->addCommand(new LedOBCGetCommandRes(m_obc->getLed()));
    }
}
