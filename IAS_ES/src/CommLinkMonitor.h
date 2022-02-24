#ifndef COMMLINKMONITOR_H
#define COMMLINKMONITOR_H

#include "PortId.h"
#include <QTimer>
#include <QObject>
#include <QHash>
#include "TransmissionQueue.h"

#define MAX_COUNT 10

//class CommManager;

enum class CommStatus
{
    NO_CONNECTED,
    CONNECTING,
    CONNECTED,
};

class CommLinkMonitor : public QObject
{
    Q_OBJECT

private:
    CommStatus m_commStatus;
    TransmissionQueue *m_transmissionQueue;
    QTimer *m_timer;
    bool m_active;
    int m_counter;
    bool m_autoUpdate;
    void setCommStatus(CommStatus status);

public:
    CommLinkMonitor(TransmissionQueue *transmissionQueue, QObject *parent = nullptr);
    void start(void);
    void stop(void);
    bool isActive(void);
    void resetCounter(void);
    void sendKeepaliveMessage(void);
    bool getAutoUpdate() const;
    void setAutoUpdate(bool autoUpdate);
    CommStatus getCommStatus() const;

signals:
    void commStatusChanged(CommStatus status);
    void autoUpdateChanged(bool autoUpdate);
};

#endif // COMMLINKMONITOR_H
