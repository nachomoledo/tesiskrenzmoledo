#ifndef COMPUTER_H
#define COMPUTER_H

#include "PortId.h"
#include "ActionFactory.h"
#include "ActionManager.h"
#include "CommManager.h"

#define COMPUTER_PORTS 2

class Computer : public QObject
{
    Q_OBJECT
private:
    QString m_name;
    ActionFactory *m_actionFactory;
    ActionManager *m_actionsManager;
    CommManager *m_commManager;
    TransmissionQueue *m_transmissionQueue;

protected:
    void setActionFactory(ActionFactory *actionFactory);
    void setActionManager(ActionManager *actionManager);
    void setCommManager(CommManager *commManager);
    void setTransmissionQueue(TransmissionQueue *transmissionQueue);

public:
    Computer(const QString &name, QObject *parent = nullptr);
    void setSerialPortName(PortId portId, const QString &serialPortName);
    void openPort(PortId portId);
    void closePort(PortId portId);
    bool isOpen(PortId portId);
    QString name() const;
    CommManager *getCommManager() const;
    TransmissionQueue *getTransmissionQueue();

};

#endif // COMPUTER_H
