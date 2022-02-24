

#ifndef ACTIONMANAGER_H
#define ACTIONMANAGER_H

/*
    Módulo que periódicamente se encarga de ejecutar las acciones
    en la cola de acciones.
*/

#include "ActionFactory.h"
#include "ActionsQueue.h"
#include <QObject>
#include <QTimer>

#define TIMER_INTERVAL_AM 10

class ActionManager : public QObject
{
    Q_OBJECT
private:
    QTimer *m_timer;
    bool m_fireTimer;
    ActionsQueue m_actionsQueue;
    void onActionAdded(void);
    void onTimeout(void);
public:
    ActionManager(QObject *parent = nullptr);
    bool addAction(Action *action);
};

#endif // ACTIONMANAGER_H
