#ifndef IMAGEMANAGERIAS_H
#define IMAGEMANAGERIAS_H

#include "ImageManager.h"


class ImageManagerIAS : public ImageManager
{
    Q_OBJECT
private:
    CameraManager *m_cameraManager;
    void checkExistingNextIdFile();
    quint16 getNextId(void);
    void setNextId(quint16 nextId);
public:
    ImageManagerIAS(TransmissionQueue *transmissionQueue, ImageDataBase *imageDataBase = nullptr, ImageEditor *imageEditor = nullptr, CameraManager *cameraManager = nullptr, QObject *parent = nullptr);
    CameraManager *getCameraManager() const;
    void captureImage(bool usingWebcam);
    void cropImage(int imageId, QList<ROI> roiList);
};

#endif // IMAGEMANAGERIAS_H
