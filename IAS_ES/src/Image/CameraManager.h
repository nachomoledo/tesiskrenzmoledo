#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include "ImageProperties.h"
#include <QRandomGenerator>

class CameraManager
{
private:
    QRandomGenerator randomGenerator;
    const QString m_imageHQPath;
    const QString m_imageLQPath;

public:
    CameraManager(QString imageBasePath);
    ImageProperties captureImageIPCam(quint16 nextId);
    ImageProperties captureImageWebcam(quint16 nextId);

};

#endif // CAMERAMANAGER_H
