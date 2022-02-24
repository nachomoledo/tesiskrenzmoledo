#include "ActionsQueue.h"
#include <QDebug>

ActionsQueue::ActionsQueue(QObject *parent) : QObject(parent)
{

}

bool ActionsQueue::addAction(Action *action)
{
    //qDebug() << "ActionsQueue::addAction";
    if (m_actionsQueue.size() >= MAX_SIZE_AQ)
    {
        return false;
    }
    else
    {
        m_actionsQueue.append(action);
        //qDebug() << "emit actionAdded";
        emit actionAdded();
        return  true;
    }
}

bool ActionsQueue::isEmpty(void)
{
    return m_actionsQueue.isEmpty();
}

Action *ActionsQueue::takeAction()
{
    if (!m_actionsQueue.isEmpty())
    {
        return m_actionsQueue.takeFirst();
    }
    else
    {
        return nullptr;
    }
}



