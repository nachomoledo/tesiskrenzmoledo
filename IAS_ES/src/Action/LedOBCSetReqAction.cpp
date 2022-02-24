#include "LedOBCSetReqAction.h"
#include <QDebug>

LedOBCSetReqAction::LedOBCSetReqAction(OnBoardComputer *obc, bool newLedStatus)
    : m_obc(obc), m_newLedStatus(newLedStatus)
{

}

void LedOBCSetReqAction::execute()
{
    //qDebug() << "LedOBCSetReqAction::execute()";
    if (m_obc)
    {
        m_obc->setLed(m_newLedStatus);
    }
}
