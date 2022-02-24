#ifndef COMMMANAGER_H
#define COMMMANAGER_H

/*
    Módulo que periódicamente se encarga de crear los paquetes
    correspondientes a los comandos en la cola de transmisión
    y pasarlos a la capa inferior para enviarlos.
*/

#include "PacketBuilder.h"
#include "ActionManager.h"
#include "SerialPortManager.h"
#include "SPIPortManager.h"
#include "TransmissionQueue.h"
#include <QObject>
#include <QTimer>
#include <QMap>
#include "ActionFactory.h"

#define TIMER_INTERVAL 100

//class ActionFactory;

class CommManager : public QObject
{
    Q_OBJECT
private:

    TransmissionQueue *m_transmissionQueue;
    PacketBuilder *m_packetFactory;
    ActionFactory *m_actionFactory;
    ActionManager *m_actionManager;
    SPIPortManager *m_spiPortManager;
    QMap<PortId, SerialPortManager*> m_serialPortManagers;
    QMap<CommandCode, PortId> m_forwardingCommands;
    QMap<CommandCode, PortId> m_knownCommands;
    QTimer *m_timer;
    bool m_fireTimer;
    void onCommandAdded(void);
    void onTimeout(void);
    void onNewPacket(QByteArray &packet);
    quint32 m_lostMessages;
    quint32 m_sentMessages;
    quint32 m_receivedMessages;
    quint32 m_sentLedOBCReqMessages;
    quint32 m_receivedLedOBCResMessages;
    quint32 m_sentLedIASReqMessages;
    quint32 m_receivedLedIASResMessages;
    void onMessageLost();
    void onMessageSent();
    void onMessageReceived();

public:
    CommManager(TransmissionQueue *transmissionQueue, ActionFactory *actionFactory, ActionManager *actionManager, QObject *parent = nullptr);
//    void startComm(void);
//    void stopComm(void);
    // TODO: AGREGAR METODO PUBLICO PARA TRANSMITIR MENSAJE
    void addPort(PortId portId, SerialPortManager* serialPortManager);
    void registerCommand(CommandCode commandCode, PortId portId);
    void registerForwardingCommand(CommandCode commandCode, PortId portId);
    SerialPortManager* getSerialPortManager(PortId portId);

    void setSentLedOBCReqMessages(const quint32 &sentLedOBCReq);
    void setReceivedLedOBCResMessages(const quint32 &receivedLedOBCRes);
    void setSentLedIASReqMessages(const quint32 &sentLedIASReq);
    void setReceivedLedIASResMessages(const quint32 &receivedLedIASRes);

signals:
    void portOpened(PortId portId);
    void portClosed(PortId portId);
    void lostMessagesChanged(quint32 total);
    void sentMessagesChanged(quint32 total);
    void receivedMessagesChanged(quint32 total);
    void sentLedOBCReqMessagesChanged(quint32 total);
    void receivedLedOBCResMessagesChanged(quint32 total);
    void sentLedIASReqMessagesChanged(quint32 total);
    void receivedLedIASResMessagesChanged(quint32 total);
};

#endif // COMMMANAGER_H
