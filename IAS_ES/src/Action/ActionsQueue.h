#ifndef ACTIONSQUEUE_H
#define ACTIONSQUEUE_H

#include "Action.h"
#include <QList>
#include <QObject>

#define MAX_SIZE_AQ 100

class ActionsQueue : public QObject
{
    Q_OBJECT

private:
    QList<Action*> m_actionsQueue;

public:
    ActionsQueue(QObject *parent = nullptr);
    bool addAction(Action *action);
    bool isEmpty(void);
    Action *takeAction(void);

signals:
    void actionAdded(void);
};

#endif // ACTIONSQUEUE_H
