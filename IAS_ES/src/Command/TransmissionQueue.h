#ifndef TRANSMISSIONQUEUE_H
#define TRANSMISSIONQUEUE_H

#include "Command.h"
#include <QList>
#include <QObject>

#define MAX_SIZE 5000

class TransmissionQueue : public QObject
{
    Q_OBJECT

private:
    QList<Command*> m_commandQueue;
    QList<Command*> m_commandQueueSPI;

public:
    TransmissionQueue(QObject *parent = nullptr);
    bool addCommand(Command *command, bool spi = false);
    bool isEmpty(bool spi = false);
    int count(bool spi = false);
    Command * takeCommand(bool spi = false);

signals:
    void commandAdded(void);
    void commandAddedSPI(void);
};

#endif // TRANSMISSIONQUEUE_H
