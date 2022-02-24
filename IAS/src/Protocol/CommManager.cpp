#include "CommManager.h"
#include "TransmissionQueue.h"
#include "ActionsQueue.h"
#include <QDebug>
#include <Defines.h>

CommManager::CommManager(TransmissionQueue *transmissionQueue, ActionFactory *actionFactory, ActionManager *actionManager, QObject *parent)
    : QObject(parent), m_transmissionQueue(transmissionQueue), m_actionFactory(actionFactory), m_actionManager(actionManager)
{
    m_lostMessages = 0;
    m_sentMessages = 0;
    m_receivedMessages = 0;
    m_sentLedOBCReqMessages = 0;
    m_receivedLedOBCResMessages = 0;
    m_sentLedIASReqMessages = 0;
    m_receivedLedIASResMessages = 0;
    m_fireTimer = false;
    m_packetFactory = new PacketBuilder();
    connect(m_transmissionQueue, &TransmissionQueue::commandAdded, this, &CommManager::onCommandAdded);
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &CommManager::onTimeout);
#ifdef IS_IAS
    m_spiPortManager = new SPIPortManager("/dev/spidev0.0", 115200);
    if (m_spiPortManager)
    {
        m_spiPortManager->openPort();
    }
    connect(m_transmissionQueue, &TransmissionQueue::commandAddedSPI, this, &CommManager::onCommandAdded);

#endif
}

void CommManager::addPort(PortId portId, SerialPortManager* serialPortManager)
{
    if (serialPortManager)
    {
        m_serialPortManagers.insert(portId, serialPortManager);
        connect(serialPortManager, &SerialPortManager::newPacket, this, &CommManager::onNewPacket);
        connect(serialPortManager, &SerialPortManager::portOpened, this, [=]{this->portOpened(portId);});
        connect(serialPortManager, &SerialPortManager::portClosed, this, [=]{this->portClosed(portId);});
        connect(serialPortManager, &SerialPortManager::messageLost, this, &CommManager::onMessageLost);
        connect(serialPortManager, &SerialPortManager::messageSent, this, &CommManager::onMessageSent);
        connect(serialPortManager, &SerialPortManager::packetSent, this, [=](quint8 commandCode, QByteArray packet){
            if (commandCode == static_cast<quint8>(CommandCode::LED_IAS_GET_REQ) || commandCode == static_cast<quint8>(CommandCode::LED_OBC_GET_REQ))
            {
                if (commandCode == static_cast<quint8>(CommandCode::LED_IAS_GET_REQ))
                {
                    setSentLedIASReqMessages(m_sentLedIASReqMessages+1);
                }
                else
                {
                    setSentLedOBCReqMessages(m_sentLedOBCReqMessages+1);
                }

//                qDebug() << "Sent (CC = " << commandCode << "): " << packet.toHex();
            }

        });
        connect(serialPortManager, &SerialPortManager::messageReceived, this, &CommManager::onMessageReceived);
    }
}

void CommManager::onMessageLost()
{
    m_lostMessages++;
    emit lostMessagesChanged(m_lostMessages);
}

void CommManager::onMessageSent()
{
    m_sentMessages++;
    emit sentMessagesChanged(m_sentMessages);
}

void CommManager::onMessageReceived()
{
    m_receivedMessages++;
    receivedMessagesChanged(m_receivedMessages);
}

void CommManager::registerCommand(CommandCode commandCode, PortId portId)
{
    m_knownCommands.insert(commandCode, portId);
}

void CommManager::registerForwardingCommand(CommandCode commandCode, PortId portId)
{
    m_forwardingCommands.insert(commandCode, portId);
}

/*!
 * \brief Dispara timer para no mandar el comando inmediatamente.
 */
void CommManager::onCommandAdded()
{
    //qDebug() << "CommManager::onCommandAdded()";
    if (false == m_fireTimer)
    {
        m_fireTimer = true;
        m_timer->start(TIMER_INTERVAL);
    }
}

SerialPortManager* CommManager::getSerialPortManager(PortId portId)
{
    if (m_serialPortManagers.contains(portId))
    {
        return m_serialPortManagers.value(portId);
    }
    return nullptr;
}

//TODO: mandar paquetes de get image response por otro puerto
void CommManager::onTimeout()
{
    bool noCommand = false;
    bool noCommandSPI = false;
    //qDebug() << "CommManager::onTimeout(void)";
    if  (!m_transmissionQueue)
    {
        return;
    }

    Command * command = m_transmissionQueue->takeCommand();
    if (command)
    {
        CommandCode commandCode = command->getCommandCode();
        if (m_knownCommands.contains(commandCode))
        {
            QByteArray packet = m_packetFactory->createPacket(command);
            //qDebug() << "onTimeout = " << packet.toHex();
            PortId portId = m_knownCommands.value(commandCode);
            SerialPortManager *serialPortManager = getSerialPortManager(portId);
            if (serialPortManager)
            {
                serialPortManager->write(packet);
//                if (/*(CommandCode::LED_IAS_SET_REQ == commandCode) || */(CommandCode::LED_IAS_GET_REQ == commandCode) )
//                {
                    //qDebug() << "Sending command (CommandCode = " << static_cast<int>(commandCode) << "): " << packet;
//                }
            }
        }
        else
        {
            //qDebug() << "Unknown command (CommandCode = " << static_cast<int>(commandCode) << ")";
        }

        delete command;
    }
    else
    {
        noCommand = true;
    }

    command = m_transmissionQueue->takeCommand(true);
    if (command)
    {
        CommandCode commandCode = command->getCommandCode();
        if (m_knownCommands.contains(commandCode))
        {
            QByteArray packet = m_packetFactory->createPacket(command);
//            qDebug() << "onTimeout SPI = " << packet.toHex();
            if (m_spiPortManager)
            {
                m_spiPortManager->write(packet);
            }
        }
        else
        {
//            qDebug() << "Unknown command SPI (CommandCode = " << static_cast<int>(commandCode) << ")";
        }

        delete command;
    }
    else
    {
        noCommandSPI = true;
    }

    if (noCommand && noCommandSPI)
    {
        //qDebug() << "CommManager::onTimeout() stop";
        m_fireTimer = false;
        m_timer->stop();
    }
}

void CommManager::onNewPacket(QByteArray &packet)
{
    //qDebug() << "CommManager::onNewPacket";

    bool validPacket = PacketValidator::isPacketValid(packet);
    if (true == validPacket)
    {
        quint8 command = packet.at(3);

//        qDebug() << "(true == validPacket) command = " << command;

        CommandCode commandCode = static_cast<CommandCode>(command);

        if (m_forwardingCommands.contains(static_cast<CommandCode>(commandCode)))
        {
            PortId portId = m_forwardingCommands.value(commandCode);
            SerialPortManager *serialPortManager = getSerialPortManager(portId);

            if (serialPortManager)
            {
                //qDebug() << "Command " << command << " forwarded to port " << static_cast<int>(portId);

                serialPortManager->write(packet);
            }
            else
            {
                //qDebug() << "ERROR: no port to foward to";
            }
        }
        else
        {
            if (commandCode == CommandCode::LED_IAS_GET_RES || commandCode == CommandCode::LED_OBC_GET_RES)
            {
                if (commandCode == CommandCode::LED_IAS_GET_RES)
                {
                    setReceivedLedIASResMessages(m_receivedLedIASResMessages+1);
                }
                else
                {
                    setReceivedLedOBCResMessages(m_receivedLedOBCResMessages+1);
                }

//                qDebug() << "Received (CC = " << command << "): " << packet.toHex();
            }


//            if ((CommandCode::LED_IAS_SET_REQ == commandCode) || (CommandCode::LED_IAS_GET_REQ == commandCode) || (CommandCode::LED_IAS_GET_RES == commandCode))
            if ((CommandCode::IMAGE_HQ_RES == commandCode))
            {
//                qDebug() << "Receiving command (CommandCode = " << static_cast<int>(commandCode) << "): " << hex << packet;
            }
            // todo: asociar comandos conocidos a acciones (algo como un mapa)
            // todo: validar comando que se reciben, parecido a lo que se hace en CommManager::onTimeout() con los de salida
            Action *action = m_actionFactory->createAction(command, packet);

            if (action && m_actionManager)
            {
                m_actionManager->addAction(action);
            }
            else
            {
                //qDebug() << "ERROR: action is null";
            }
        }
    }
    else
    {
//        qDebug() << "(false == validPacket)";
    }
}

void CommManager::setReceivedLedIASResMessages(const quint32 &receivedLedIASRes)
{
    if (m_receivedLedIASResMessages  != receivedLedIASRes)
    {
        m_receivedLedIASResMessages = receivedLedIASRes;
        emit receivedLedIASResMessagesChanged(m_receivedLedIASResMessages);
    }

}

void CommManager::setSentLedIASReqMessages(const quint32 &sentLedIASReq)
{
    if (m_sentLedIASReqMessages != sentLedIASReq)
    {
        m_sentLedIASReqMessages = sentLedIASReq;
        emit sentLedIASReqMessagesChanged(m_sentLedIASReqMessages);

    }
}

void CommManager::setReceivedLedOBCResMessages(const quint32 &receivedLedOBCRes)
{
    if (m_receivedLedOBCResMessages != receivedLedOBCRes)
    {
        m_receivedLedOBCResMessages = receivedLedOBCRes;
        emit receivedLedOBCResMessagesChanged(m_receivedLedOBCResMessages);
    }
}

void CommManager::setSentLedOBCReqMessages(const quint32 &sentLedOBCReq)
{
    if (m_sentLedOBCReqMessages != sentLedOBCReq)
    {
        m_sentLedOBCReqMessages = sentLedOBCReq;
        emit sentLedOBCReqMessagesChanged(m_sentLedOBCReqMessages);

    }
}
