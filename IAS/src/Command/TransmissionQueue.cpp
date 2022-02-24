#include "TransmissionQueue.h"
#include <QDebug>

TransmissionQueue::TransmissionQueue(QObject *parent) : QObject(parent)
{

}

bool TransmissionQueue::addCommand(Command *command, bool spi)
{
    QList<Command*> *queue = !spi ? &m_commandQueue : &m_commandQueueSPI;
    if (queue->size() >= MAX_SIZE)
    {
        return false;
    }
    else
    {
        queue->append(command);
//        //qDebug() << "TransmissionQueue::addCommand: emit commandAdded()";
        if (!spi)
        {
            emit commandAdded();
        }
        else
        {
            emit commandAddedSPI();
        }
        return  true;
    }
}

bool TransmissionQueue::isEmpty(bool spi)
{
    QList<Command*> *queue = !spi ? &m_commandQueue : &m_commandQueueSPI;
    return queue->isEmpty();
}

Command *TransmissionQueue::takeCommand(bool spi)
{
    QList<Command*> *queue = !spi ? &m_commandQueue : &m_commandQueueSPI;
    if (!(queue->isEmpty()))
    {
        return queue->takeFirst();
    }
    else
    {
        return nullptr;
    }
}

int TransmissionQueue::count(bool spi)
{
    QList<Command*> *queue = !spi ? &m_commandQueue : &m_commandQueueSPI;
    return queue->count();
}




