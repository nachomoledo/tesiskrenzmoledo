#include "LedIASSetReqAction.h"
#include <QDebug>
#include <Defines.h>

#ifndef LED_SIMULATION
#include <wiringPi.h>
#endif

LedIASSetReqAction::LedIASSetReqAction(ImageAcquisitionSystem *ias, bool newLedStatus)
    : m_ias(ias), m_newLedStatus(newLedStatus)
{

}

void LedIASSetReqAction::execute()
{
    //qDebug() << "LedIASSetReqAction::execute()";          
#ifdef LED_SIMULATION
    if (m_ias)
    {
        m_ias->setLed(m_newLedStatus);
    }
#else
    int ledPin = 29;  //Corresponde al pin 40

    if(wiringPiSetup() < 0)
    {
        //qDebug() << "setup wiring pi failed";
    }
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, static_cast<int>(m_newLedStatus));
#endif
}
