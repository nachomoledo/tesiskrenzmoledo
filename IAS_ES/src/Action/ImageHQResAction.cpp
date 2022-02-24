#include "ImageHQResAction.h"

#include "Defines.h"
#include <QDebug>
//#include <stdio.h>
#include <QFile>
#include <ImageHQCommandRes.h>

ImageHQResAction::ImageHQResAction(QString imagePath, int packetNumber, int totalPackets, QByteArray imageData)
    : m_imagePath(imagePath), m_packetNumber(packetNumber), m_totalPackets(totalPackets), m_imageData(imageData)
{
    static int id = 0;
//    qDebug() << "constructor " << id++ << ": " << m_imageData.toHex();
    //qDebug() << "ImageHQResAction::packetNumber = " << m_imagePath;
    //qDebug() << "ImageHQResAction::packetNumber = " << m_packetNumber;
    //qDebug() << "ImageHQResAction::totalPackets = " << m_totalPackets;
    //qDebug() << "ImageHQResAction::imageData = " << m_imageData.toHex();

}

void ImageHQResAction::execute()
{
    static int id = 0;
    //Crea archivo de la imagen si no existe
    QString imageName = QString("%1%2").arg(m_imagePath).arg(HIGH_QUALITY_EXTENSION);
    //qDebug() << "ImageHQResAction::execute() imageName = |" << imageName << "|";
    qDebug() << "execute " << id++ << ": " << m_imageData.toHex();
    QFile file(imageName);
    QString errMsg;
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        errMsg = file.errorString();
        //qDebug() << "Error al abrir la imagen: " << errMsg;
        return;
    }

    //012 - BIEN
    //345 - MAL
    //678 - BIEN
    //9
    int fileSize = file.size();
    int expectedSize = (m_packetNumber-1)*PKT_DATA_MAX;

    if (fileSize != expectedSize)
    {
        int diff = expectedSize - fileSize;
        QByteArray lostData = QByteArray(diff, 0);
        file.write(lostData);
    }

    file.write(m_imageData);
    file.close();
}
