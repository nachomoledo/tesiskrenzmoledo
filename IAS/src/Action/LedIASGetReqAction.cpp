#include "LedIASGetReqAction.h"
#include "LedIASGetCommandRes.h"
#include <QDebug>
#include <Defines.h>

#ifndef LED_SIMULATION
#include <wiringPi.h>
#endif

LedIASGetReqAction::LedIASGetReqAction(ImageAcquisitionSystem *ias, TransmissionQueue *transmissionQueue)
    : m_ias(ias), m_transmissionQueue(transmissionQueue)
{

}

void LedIASGetReqAction::execute()
{
    //qDebug() << "LedIASGetAction::execute()";
#ifdef LED_SIMULATION
    if (m_ias && m_transmissionQueue)
    {
        m_transmissionQueue->addCommand(new LedIASGetCommandRes(m_ias->getLed()));
    }
#else

    int ledPin = 29;  //Corresponde al pin 40

    if(wiringPiSetup() < 0)
    {
        //qDebug() << "setup wiring pi failed";
    }

    pinMode(ledPin, OUTPUT);

    if (m_transmissionQueue)
    {
        m_transmissionQueue->addCommand(new LedIASGetCommandRes(digitalRead(ledPin)));
    }
#endif

}
