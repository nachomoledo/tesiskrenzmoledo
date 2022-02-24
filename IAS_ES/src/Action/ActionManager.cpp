#include "ActionManager.h"
#include "ActionsQueue.h"
#include <QDebug>

ActionManager::ActionManager(QObject *parent) : QObject(parent)
{
    m_fireTimer = false;
    connect(&m_actionsQueue, &ActionsQueue::actionAdded, this, &ActionManager::onActionAdded);
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &ActionManager::onTimeout);
}

void ActionManager::onActionAdded(void)
{
    //qDebug() << "ActionsManager::onActionAdded";
    if (false == m_fireTimer)
    {
        m_fireTimer = true;
        m_timer->start(TIMER_INTERVAL_AM);
    }
}

void ActionManager::onTimeout(void)
{
    Action *action = m_actionsQueue.takeAction();
    if (nullptr != action)
    {
        action->execute();
        delete action;
    }
}

bool ActionManager::addAction(Action *action)
{
    //qDebug() << "ActionManager::addAction";
    return m_actionsQueue.addAction(action);
}
