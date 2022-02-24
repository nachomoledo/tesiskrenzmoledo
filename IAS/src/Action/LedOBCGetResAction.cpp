#include "LedOBCGetResAction.h"
#include <QDebug>

LedOBCGetResAction::LedOBCGetResAction(EarthStation *earthStation, bool stateToSet)
    : m_earthStation(earthStation), m_stateToSet(stateToSet)
{

}

void LedOBCGetResAction::execute()
{
    //qDebug() << "LedOBCGetResAction::execute()";
    if (m_earthStation)
    {
        m_earthStation->setOBCLedStatus(m_stateToSet);
    }
}
