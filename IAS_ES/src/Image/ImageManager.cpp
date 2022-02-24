#include "ImageManager.h"
#include <ImageHQCommandReq.h>
#include <ImageLQCommandReq.h>
#include <CatalogCommandReq.h>
#include <DeleteCommandReq.h>
#include <CaptureCommandReq.h>
#include "ImageEditor.h"
#include "Defines.h"
#include <QDebug>

ImageManager::ImageManager(TransmissionQueue *transmissionQueue, ImageDataBase *imageDataBase, ImageEditor *imageEditor, QObject *parent)
    : QObject(parent), m_transmissionQueue(transmissionQueue), m_imageDataBase(imageDataBase), m_imageEditor(imageEditor)
{

}

ImageEditor *ImageManager::getImageEditor() const
{
    return m_imageEditor;
}

ImageDataBase *ImageManager::getImageDataBase() const
{
    return m_imageDataBase;
}

void ImageManager::sendImageCommandReqMessage(unsigned short imageId, quint8 quality)
{
    //qDebug() << "ImageManager::sendImageCommandReqMessage(" << imageId << ", quality = " << quality << ")";
    if (m_transmissionQueue)
    {
        if (IMAGE_QUALITY_HIGH == quality)
        {
            m_transmissionQueue->addCommand(new ImageHQCommandReq(imageId));
        }
        else if (IMAGE_QUALITY_LOW == quality)
        {
            m_transmissionQueue->addCommand(new ImageLQCommandReq(imageId));
        }
    }
}

void ImageManager::sendCaptureReqMessage(bool usingWebcam)
{
    //qDebug() << "ImageManager::sendCaptureReqMessage()";
    if (m_transmissionQueue)
    {
        m_transmissionQueue->addCommand(new CaptureCommandReq(usingWebcam));
    }
}

void ImageManager::sendCatalogCommandReqMessage(void)
{
    //qDebug() << "ImageManager::sendCatalogCommandReqMessage()";
    if (m_transmissionQueue && m_imageDataBase)
    {
        m_imageDataBase->createCatalogBackup();
        m_imageDataBase->clearImageMapAux();
        m_transmissionQueue->addCommand(new CatalogCommandReq());
    }
}

void ImageManager::sendDeleteReqMessage(int id)
{
    if (m_transmissionQueue)
    {
        QList<quint16> list;
        list.append(id);
        m_transmissionQueue->addCommand(new DeleteCommandReq(list));
    }
}

void ImageManager::selectROI(int imageId)
{
    if (m_transmissionQueue && m_imageDataBase)
    {
        QString imageName = m_imageDataBase->getImageBasePathAndNameWithExtension(imageId, LOW_QUALITY_EXTENSION);
        QList<ROI> roiList = ImageEditor::selectROI(imageName);
        if (!roiList.isEmpty())
        {
            m_transmissionQueue->addCommand(new CropCommandReq(imageId, roiList));
        }
    }
}
