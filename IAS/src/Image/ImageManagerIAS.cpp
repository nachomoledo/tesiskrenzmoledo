#include "ImageManagerIAS.h"
#include "Defines.h"
#include "Files.h"
#include <QFile>
#include <QDateTime>
#include <QtConcurrent>
#include <QDebug>

// FIXME: no tendría que ser absoluto, pasar como parametro en main()
#define NEXTID_FILE "nextId.txt"

ImageManagerIAS::ImageManagerIAS(TransmissionQueue *transmissionQueue, ImageDataBase *imageDataBase, ImageEditor *imageEditor, CameraManager *cameraManager, QObject *parent)
    : ImageManager(transmissionQueue, imageDataBase, imageEditor, parent), m_cameraManager(cameraManager)
{
    checkExistingNextIdFile();
}

void ImageManagerIAS::checkExistingNextIdFile()
{
    QFile file(m_imageDataBase->getImageDBPath() + NEXTID_FILE);

    if (!file.open(QIODevice::NewOnly))
    {
        //qDebug() << "NEXT ID FILE ALREADY EXISTS (" << m_imageDataBase->getImageDBPath() + NEXTID_FILE << "): " << file.errorString();
        return;
    }

    file.putChar('1');

    file.close();
}

void ImageManagerIAS::captureImage(bool usingWebcam)
{
    quint16 id = 0;

    if (!m_imageDataBase)
    {
        //qDebug() << "ERROR: Image Data Base is not set";
        return;
    }


    if (!m_cameraManager)
    {
        //qDebug() << "ERROR: Camera Manager is not set";
        return;
    }

    //qDebug() << "begin CaptureReqAction::execute";

    id = getNextId();
    ImageProperties imageProperties;

    if (usingWebcam)
    {
        imageProperties = m_cameraManager->captureImageWebcam(id);
    }
    else
    {
        imageProperties = m_cameraManager->captureImageIPCam(id);
    }

    if ((imageProperties.getId() != 0) && (imageProperties.getSize() != "0"))
    {
        m_imageDataBase->registerImage(imageProperties.getId(),
                                       imageProperties.getSize(),
                                       imageProperties.getWidth(),
                                       imageProperties.getHeight(),
                                       imageProperties.getTimestamp());

        id++;
        setNextId(id);

    }
    else
    {
        //qDebug() << "ERROR: cannot set next id or image is null";
    }

    //qDebug() << "end CaptureReqAction::execute";
}

void ImageManagerIAS::cropImage(int imageId, QList<ROI> roiList)
{
    //qDebug() << "begin ImageManager::cropImage";

    if (!m_imageDataBase)
    {
        //qDebug() << "ERROR: Image Data Base is not set";
        return;
    }


    for (int i = 0; i < roiList.size(); i++)
    {
        quint16 nextId = getNextId();
        if (0 == nextId)
        {
            //qDebug() << "ERROR: cannot set next id";
            continue;
        }
        ROI roi = roiList.at(i);
        QString imgName1 = m_imageDataBase->getImageBasePathAndNameWithExtension(imageId, HIGH_QUALITY_EXTENSION);
        QString cropImgName1 = m_imageDataBase->getImageHQPath() + QString::number(nextId) + HIGH_QUALITY_EXTENSION;
        int size1 = ImageEditor::cropImage(imgName1, roi, cropImgName1, HIGH_QUALITY_EXTENSION);
        QString imgName2 = m_imageDataBase->getImageBasePathAndNameWithExtension(imageId, LOW_QUALITY_EXTENSION);
        QString cropImgName2 = m_imageDataBase->getImageLQPath() + QString::number(nextId) + LOW_QUALITY_EXTENSION;
        int size2 = ImageEditor::cropImage(imgName2, roi, cropImgName2, LOW_QUALITY_EXTENSION);
        //qDebug() << "size1 = " << size1 << ", size2 = " << size2;
        if ((size1 != 0) && (size2 != 0))
        {
            ImageProperties imageProperties(nextId, QString::number(size1), QString::number(roi.width), QString::number(roi.height), QDateTime::currentSecsSinceEpoch());

            m_imageDataBase->registerImage(imageProperties.getId(),
                                           imageProperties.getSize(),
                                           imageProperties.getWidth(),
                                           imageProperties.getHeight(),
                                           imageProperties.getTimestamp());

            nextId++;
            setNextId(nextId);
        }
        //qDebug() << "ImageEditor::cropImage(roiList[" << i << "] = ROI(x = " << roi.x << ", y = " << roi.y << ", w = " << roi.width << ", h = " << roi.height << "))";
    }

    //qDebug() << "end ImageManager::cropImage";
}

CameraManager *ImageManagerIAS::getCameraManager() const
{
    return m_cameraManager;
}


quint16 ImageManagerIAS::getNextId(void)
{
    //qDebug() << "CameraManager::getNextId()";
    QFile file(m_imageDataBase->getImageDBPath() + NEXTID_FILE);
    if (!file.open(QIODevice::ReadOnly)) {
        //qDebug() << "ERROR READING FILE " << m_imageDataBase->getImageDBPath() + NEXTID_FILE << ": " << file.errorString();
        return 0;
    }

    //qDebug() << "File " << m_imageDataBase->getImageDBPath() + NEXTID_FILE << " opened successfuly";

    bool ok = false;
    /* Se lee y descarta la primera línea ya que es el nextId y no una ImageProperty*/
    QByteArray line = file.readLine();
    QStringList wordList = Files::processLine(line);
    file.close();
    if (wordList.size() != 1)
    {
        //qDebug() << "Reading next id failed";
        return 0;
    }
    else
    {
        quint16 retValue = wordList.at(0).toUInt(&ok);
        if (ok)
        {
            return retValue;
        }
    }
    return 0;
}


void ImageManagerIAS::setNextId(quint16 nextId)
{
    QFile file(m_imageDataBase->getImageDBPath() + NEXTID_FILE);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
    {
        //qDebug() << "ERROR READING FILE " << m_imageDataBase->getImageDBPath() + NEXTID_FILE << ": " << file.errorString();
        /* TODO: retornar código de error */
    }

    //qDebug() << "File " << m_imageDataBase->getImageDBPath() + NEXTID_FILE << " opened successfuly";

    QTextStream out(&file);
    out << QString::number(nextId) << "\n";
    file.close();
}
