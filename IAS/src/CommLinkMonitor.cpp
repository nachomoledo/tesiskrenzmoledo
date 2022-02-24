#include "CommLinkMonitor.h"
#include "KeepaliveCommandReq.h"
#include <QDebug>
//#include "CommManager.h"

bool CommLinkMonitor::getAutoUpdate() const
{
    return m_autoUpdate;
}

void CommLinkMonitor::setAutoUpdate(bool autoUpdate)
{
    //qDebug() << "CommLinkMonitor::setAutoUpdate(autoUpdate = " << autoUpdate << ")";
    if (autoUpdate != m_autoUpdate)
    {
        m_autoUpdate = autoUpdate;
        emit autoUpdateChanged(autoUpdate);
    }
}

CommLinkMonitor::CommLinkMonitor(TransmissionQueue *transmissionQueue, QObject *parent)
    : QObject(parent), m_transmissionQueue(transmissionQueue)
{
    m_commStatus = CommStatus::NO_CONNECTED;
    m_timer = new QTimer();
    connect(m_timer, &QTimer::timeout, this, &CommLinkMonitor::sendKeepaliveMessage);
    m_active = false;
    m_counter = 0;
    m_autoUpdate = false;
}

void CommLinkMonitor::start()
{
    if (m_transmissionQueue/* && m_commManager->getSerialPortManager(PortId::ES_OBC_PORT) && m_commManager->getSerialPortManager(PortId::ES_OBC_PORT)->isOpen()*/)
    {
        m_timer->start(5000);
        m_active = true;
        //qDebug() << "CommLinkMonitor started!";
        setCommStatus(CommStatus::CONNECTING);
    }
    else
    {
        //qDebug() << "ERROR: serial port manager is not open";
    }
}

void CommLinkMonitor::stop()
{
    m_timer->stop();
    m_active = false;
    setCommStatus(CommStatus::NO_CONNECTED);
}

bool CommLinkMonitor::isActive()
{
    return m_active;
}

void CommLinkMonitor::sendKeepaliveMessage()
{
    //qDebug() << "CommLinkMonitor::sendKeepaliveMessage()";
    if (m_counter < MAX_COUNT)
    {
        if (m_transmissionQueue && m_transmissionQueue->addCommand(new KeepaliveCommandReq()))
        {
            m_counter++;
        }
    }
    else
    {
        setCommStatus(CommStatus::NO_CONNECTED);
    }
}

void CommLinkMonitor::resetCounter(void)
{
    //qDebug() << "CommLinkMonitor::resetCounter";
    m_counter = 0;
    setCommStatus(CommStatus::CONNECTED);
}

CommStatus CommLinkMonitor::getCommStatus() const
{
    return m_commStatus;
}

void CommLinkMonitor::setCommStatus(CommStatus status)
{
    if (m_commStatus != status)
    {
        m_commStatus = status;
        emit commStatusChanged(m_commStatus);
    }
}

