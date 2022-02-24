#ifndef EARTHSTATION_H
#define EARTHSTATION_H

#include "Computer.h"
#include "ImageManager.h"
#include "ErrorManager.h"

class EarthStation : public Computer
{
    Q_OBJECT
private:
    ErrorManager *m_errorManager;
    ImageManager *m_imageManager;
    CommLinkMonitor *m_commLinkMonitor;
    /* Para pedir estado led ias */
    QTimer *m_timer;
    //TODO: construir action factory y ver como refactorizar el tipo
    bool m_iasLedStatus;
    bool m_obcLedStatus;
public:
//    EarthStation() : Computer(""){};
    EarthStation(QString name, QString basePath, QObject *parent = nullptr);
    ImageManager *getImageManager() const;
    CommLinkMonitor *getCommLinkMonitor() const;
    ErrorManager *getErrorManager() const;
    bool getIASLedStatus() const;
    void setIASLedStatus(bool iasLedStatus);
    bool getOBCLedStatus() const;
    void setOBCLedStatus(bool OBCLedStatus);
signals:
    void iasLedStatusChanged(void);
    void obcLedStatusChanged(void);
};

#endif // EARTHSTATION_H
