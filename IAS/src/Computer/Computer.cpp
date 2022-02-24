#include "Computer.h"
#include <QDebug>

QString Computer::name() const
{
    return m_name;
}

Computer::Computer(const QString &name, QObject *parent)
    : QObject(parent), m_name(name)
{
    m_actionFactory = nullptr;
    m_actionsManager = nullptr;
    m_commManager = nullptr;
    m_transmissionQueue = nullptr;
}

void Computer::setSerialPortName(PortId portId, const QString &serialPortName)
{
    if (m_commManager)
    {
        SerialPortManager* serialPortManager = m_commManager->getSerialPortManager(portId);

        if (serialPortManager)
        {
            serialPortManager->setSerialPortName(serialPortName);
        }
    }
}

void Computer::openPort(PortId portId)
{
    if (m_commManager)
    {
        SerialPortManager* serialPortManager = m_commManager->getSerialPortManager(portId);

        if (serialPortManager)
        {
            if(serialPortManager->openPort())
            {
                qDebug() << "Port " << serialPortManager->getSerialPortName() << " opened successfully.";

            }
            else
            {
                QString name = serialPortManager->getSerialPortName();
               qDebug() << "Error opening " << name << ".";
            }
        }
        else
        {
            //qDebug() << "Invalid serial port id (" << static_cast<int>(portId) << ".";
        }
    }
}

void Computer::closePort(PortId portId)
{
    if (m_commManager)
    {
        SerialPortManager* serialPortManager = m_commManager->getSerialPortManager(portId);

        if (serialPortManager && serialPortManager->isOpen())
        {
            serialPortManager->closePort();
            //qDebug() << "Port " << serialPortManager->getSerialPortName() << " closed.";
        }
    }
}

bool Computer::isOpen(PortId portId)
{
    if (m_commManager)
    {
        SerialPortManager* serialPortManager = m_commManager->getSerialPortManager(portId);

        if (serialPortManager)
        {
            return serialPortManager->isOpen();
        }
    }
    return false;
}

CommManager *Computer::getCommManager() const
{
    return m_commManager;
}

TransmissionQueue *Computer::getTransmissionQueue()
{
    return m_transmissionQueue;
}

void Computer::setActionFactory(ActionFactory *actionFactory)
{
    m_actionFactory = actionFactory;
}

void Computer::setActionManager(ActionManager *actionManager)
{
    m_actionsManager = actionManager;
}

void Computer::setCommManager(CommManager *commManager)
{
    m_commManager = commManager;
}

void Computer::setTransmissionQueue(TransmissionQueue *transmissionQueue)
{
    m_transmissionQueue = transmissionQueue;
}
