#include "LedIASGetResAction.h"
#include <QDebug>

LedIASGetResAction::LedIASGetResAction(EarthStation *earthStation, bool stateToSet)
    : m_earthStation(earthStation), m_stateToSet(stateToSet)
{

}

void LedIASGetResAction::execute()
{
    //qDebug() << "LedIASGetResAction::execute()";
    if (m_earthStation)
    {
        m_earthStation->setIASLedStatus(m_stateToSet);
    }
}
