#include "CameraManager.h"
#include "Defines.h"
#include <QDebug>
#include <QImage>
#include <QDateTime>
#include <QtConcurrent>

#define IMAGE_FILE "/home/tesis/Repos/TESIS_V2/res/image.bmp"
#define IMAGE_FILE2 "/home/tesis/Repos/TESIS_V2/res/image.jpg"

#define MIN_WIDTH 128
#define MIN_HEIGHT 128
#define MAX_WIDTH 1366
#define MAX_HEIGHT 768


CameraManager::CameraManager(QString imageBasePath)
    : m_imageHQPath(imageBasePath + "/hq/"), m_imageLQPath(imageBasePath + "/lq/")
{

}

ImageProperties CameraManager::captureImageWebcam(quint16 nextId)
{

    QString LQpath;
    QString HQpath;
    QString command;

    LQpath.append(m_imageLQPath).append(QString::number(nextId)).append(LOW_QUALITY_EXTENSION);

    command.append("fswebcam -r ").append(IMAGE_RESOLUTION)
            .append(" --no-banner ").append(LQpath);

    system(command.toLocal8Bit().data());

    QImage image(LQpath);
    image = image.scaled(400, 300, Qt::KeepAspectRatio);
    image.save(LQpath, "JPG");

    HQpath.append(m_imageHQPath).append(QString::number(nextId)).append(HIGH_QUALITY_EXTENSION);
    image.save(HQpath, "BMP");

    return ImageProperties(nextId, QString::number(image.sizeInBytes()), QString::number(image.width()), QString::number(image.height()), QDateTime::currentSecsSinceEpoch());
}

ImageProperties CameraManager::captureImageIPCam(quint16 nextId)
{
    int randomWidth = randomGenerator.bounded(MIN_WIDTH, MAX_WIDTH+1);
    int randomHeight = randomGenerator.bounded(MIN_HEIGHT, MAX_HEIGHT+1);
    int randomX = randomGenerator.bounded(0, MAX_WIDTH-randomWidth);
    int randomY = randomGenerator.bounded(0, MAX_HEIGHT-randomHeight);
    QImage image(IMAGE_FILE);
    QImage newImage = image.copy(randomX, randomY, randomWidth, randomHeight);
    newImage.save(m_imageHQPath + QString::number(nextId) + ".bmp");
    QImage image2(IMAGE_FILE2);
    QImage newImage2 = image2.copy(randomX, randomY, randomWidth, randomHeight);
    newImage2.save(m_imageLQPath + QString::number(nextId) + ".jpg");
    return ImageProperties(nextId, QString::number(newImage.sizeInBytes()), QString::number(randomWidth), QString::number(randomHeight), QDateTime::currentSecsSinceEpoch());
}
