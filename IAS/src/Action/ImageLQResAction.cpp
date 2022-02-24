#include "ImageLQResAction.h"

#include "Defines.h"
#include <QDebug>
//#include <stdio.h>
#include <QFile>
#include <ImageLQCommandRes.h>

ImageLQResAction::ImageLQResAction(QString imagePath, int packetNumber, int totalPackets, QByteArray imageData)
    : m_imagePath(imagePath), m_packetNumber(packetNumber), m_totalPackets(totalPackets), m_imageData(imageData)
{
    //qDebug() << "packetNumber = " << packetNumber;
    //qDebug() << "totalPackets = " << totalPackets;
    //qDebug() << "imageData = " << imageData.toHex();

}

void ImageLQResAction::execute()
{
    //Crea archivo de la imagen si no existe
    QString imageName = QString("%1%2").arg(m_imagePath).arg(LOW_QUALITY_EXTENSION);
    //qDebug() << "ImageLQResAction::execute() imageName = |" << imageName << "|";
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
