#include "ImageHQReqAction.h"
#include <QDebug>
//#include <stdio.h>
#include <QFile>
#include <ImageHQCommandRes.h>
#include <Defines.h>

ImageHQReqAction::ImageHQReqAction(TransmissionQueue *transmissionQueue, unsigned short id, QString imagePath)
    : m_transmissionQueue(transmissionQueue), m_imageId(id), m_imagePath(imagePath)
{
}

void ImageHQReqAction::execute()
{
    //Abre la imagen a leer.
    QFile file(m_imagePath);
    QString errMsg;
    if (!file.exists()) {
        //qDebug() << "No existe la imagen";
        return;
    }
    else if (!file.open(QIODevice::ReadOnly))
    {
        errMsg = file.errorString();
        //qDebug() << "Error al abrir la imagen: " << errMsg;
        return;
    }

    if (!m_transmissionQueue)
    {
        //qDebug() << "ERROR: no se pueden enviar mensajes";
    }

    QByteArray imageData = file.readAll();

//    /*TransmissionQueue::getInstance().addCommand(new GetImageRequestCommand(""));*/

    int imageSize = imageData.size();
    //qDebug() << "imageSize = " << imageSize;

    int totalPackets = imageSize/PKT_DATA_MAX;
    //qDebug() << "totalPackets = " << totalPackets;

    if (imageSize%PKT_DATA_MAX) //Si la división no es entera se manda un paquete extra con datos < MAXDATA
    {
        totalPackets++;
    }

    QByteArray data;

    for (int i = 0; i < totalPackets; i++)
    {
        data = imageData;
        data = data.right(imageSize-(i*PKT_DATA_MAX));
        data.truncate(PKT_DATA_MAX);
#ifndef IS_SIMULATION
        m_transmissionQueue->addCommand(new ImageHQCommandRes(m_imageId, i+1, totalPackets, data));
#else
        m_transmissionQueue->addCommand(new ImageHQCommandRes(m_imageId, i+1, totalPackets, data), true);
#endif
}

    file.close();

//    QByteArray imageId;
//    imageId.append(0xAA);
//    imageId.append(0xAA);

//    int packetNumber = 0;
//    //60000
//    QByteArray



    /*
    definir tamaño máximo de bytes de la imagen por paquete (120)
    definir tamaño máximo id imagen (2 bytes o 65535)
    definir tamaño máximo de paquetes por imagen (3 bytes o 2 a la 24)
    esto da como resultado tamaño máximo de las imágenes
    crear tabla id - nombre imagen (catalogo?)
    Payload:
    2 bytes - ID imagen
    4 bytes - numero de paquete de la imagen
    4 bytes - total de paquetes de la imagen
    n hasta 118 bytes - datos de la imagen
    al no haber ack, debe haber un timeout por paquete y rellenar con color negro si no llego el paquete y vino el siguiente
    este excecute generaría y mandaría todos los comandos a la transmissionqueue
*/
}
