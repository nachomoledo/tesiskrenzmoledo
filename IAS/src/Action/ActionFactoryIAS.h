#ifndef ACTIONFACTORYIAS_H
#define ACTIONFACTORYIAS_H

#include "ActionFactory.h"
#include "ImageDataBase.h"
#include <QString>
#include "TransmissionQueue.h"
#include "CommLinkMonitor.h"
#include "ImageManagerIAS.h"
#include "ImageAcquisitionSystem.h"

class ActionFactoryIAS : public ActionFactory
{
private:
    Action *createLedIASSetReqAction(const QByteArray &packet);
    Action *createLedIASGetReqAction(const QByteArray &packet);
    Action *createKeepaliveReqAction(const QByteArray &packet);
    Action *createCropReqAction(const QByteArray &packet);
    Action *createImageHQReqAction(const QByteArray &packet);
    Action *createImageLQReqAction(const QByteArray &packet);
    Action *createCatalogReqAction(const QByteArray &packet);
    Action *createDeleteReqAction(const QByteArray &packet);
    Action *createCaptureReqAction(const QByteArray &packet);
    ImageAcquisitionSystem *m_ias;
    TransmissionQueue* m_transmissionQueue;
    ImageDataBase *m_imageDataBase;
    ImageManagerIAS *m_imageManagerIAS;

public:
    ActionFactoryIAS(ImageAcquisitionSystem *ias, TransmissionQueue *transmissionQueue = nullptr, ImageDataBase *imgDataBase = nullptr, ImageManagerIAS *imageManagerIAS = nullptr);
};

#endif // ACTIONFACTORYIAS_H
