#ifndef ACTIONFACTORYES_H
#define ACTIONFACTORYES_H

#include "ActionFactory.h"
#include "ImageDataBase.h"
#include "TransmissionQueue.h"
#include "CommLinkMonitor.h"
#include "ImageManager.h"
#include "EarthStation.h"

#include <QString>

class ActionFactoryES : public ActionFactory
{
private:
    Action *createKeepaliveResAction(const QByteArray &packet);
    Action *createImageHQResAction(const QByteArray &packet);
    Action *createImageLQResAction(const QByteArray &packet);
    Action *createCatalogResAction(const QByteArray &packet);
    Action *createLedIASGetResAction(const QByteArray &packet);
    Action *createLedOBCGetResAction(const QByteArray &packet);
    EarthStation *m_earthStation;
    TransmissionQueue* m_transmissionQueue;
    CommLinkMonitor* m_commLinkMonitor;
    ImageDataBase *m_imageDataBase;
    ImageManager *m_imageManager;
    //Fixme: al pasarle la earth station ya no tengo que pasar todo por separado

public:
    ActionFactoryES(EarthStation *earthStation = nullptr, TransmissionQueue *transmissionQueue = nullptr, CommLinkMonitor *clm = nullptr, ImageDataBase *imgDataBase = nullptr, ImageManager *imageManager = nullptr);
    Action *createAction(quint8 commandId, const QByteArray &packet);
};

#endif // ACTIONFACTORYES_H
