#ifndef IMAGETRANSMITTER_H
#define IMAGETRANSMITTER_H

#include "TransmissionQueue.h"
#include "ImageDataBase.h"
#include "ImageEditor.h"
#include "CameraManager.h"
#include <QObject>


class ImageManager : public QObject
{
    Q_OBJECT
protected:
    TransmissionQueue *m_transmissionQueue;
    ImageDataBase *m_imageDataBase;
    ImageEditor *m_imageEditor;

public:
    ImageManager(TransmissionQueue *transmissionQueue, ImageDataBase *imageDataBase = nullptr, ImageEditor *imageEditor = nullptr, QObject *parent = nullptr);
    Q_INVOKABLE void sendImageCommandReqMessage(unsigned short imageId, quint8 quality);
    Q_INVOKABLE void sendCatalogCommandReqMessage(void);
    Q_INVOKABLE void sendDeleteReqMessage(int imageId);
    Q_INVOKABLE void selectROI(int imageId);
    ImageDataBase *getImageDataBase() const;
    void sendCaptureReqMessage(bool usingWebcam);
    ImageEditor *getImageEditor() const;

};

#endif // IMAGETRANSMITTER_H
