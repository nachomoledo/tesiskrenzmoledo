#include "ActionFactoryIAS.h"
#include "KeepaliveReqAction.h"
#include "CropReqAction.h"
#include "ImageHQReqAction.h"
#include "ImageLQReqAction.h"
#include "CatalogReqAction.h"
#include "CaptureReqAction.h"
#include "DeleteReqAction.h"
#include "LedIASGetReqAction.h"
#include "LedIASSetReqAction.h"
#include "PacketReader.h"
#include "Defines.h"
#include <QList>
#include <QDebug>

ActionFactoryIAS::ActionFactoryIAS(ImageAcquisitionSystem *ias, TransmissionQueue *transmissionQueue, ImageDataBase *imgDataBase, ImageManagerIAS *imageManagerIAS)
    : ActionFactory(), m_ias(ias), m_transmissionQueue(transmissionQueue), m_imageDataBase(imgDataBase), m_imageManagerIAS(imageManagerIAS)
{    
    registerCreateActionFn(static_cast<quint8>(CommandCode::LED_IAS_GET_REQ), [=](const QByteArray &packet) { return this->createLedIASGetReqAction(packet);});
    registerCreateActionFn(static_cast<quint8>(CommandCode::LED_IAS_SET_REQ), [=](const QByteArray &packet) { return this->createLedIASSetReqAction(packet);});
    registerCreateActionFn(static_cast<quint8>(CommandCode::KEEPALIVE_REQ), [=](const QByteArray &packet) { return this->createKeepaliveReqAction(packet);});
    registerCreateActionFn(static_cast<quint8>(CommandCode::CAPTURE_REQ), [=](const QByteArray &packet) { return this->createCaptureReqAction(packet);});
    registerCreateActionFn(static_cast<quint8>(CommandCode::CROP_REQ), [=](const QByteArray &packet) { return this->createCropReqAction(packet);});
    registerCreateActionFn(static_cast<quint8>(CommandCode::IMAGE_HQ_REQ), [=](const QByteArray &packet) { return this->createImageHQReqAction(packet);});
    registerCreateActionFn(static_cast<quint8>(CommandCode::IMAGE_LQ_REQ), [=](const QByteArray &packet) { return this->createImageLQReqAction(packet);});
    registerCreateActionFn(static_cast<quint8>(CommandCode::CATALOG_REQ), [=](const QByteArray &packet) { return this->createCatalogReqAction(packet);});
    registerCreateActionFn(static_cast<quint8>(CommandCode::DELETE_REQ), [=](const QByteArray &packet) { return this->createDeleteReqAction(packet);});
}

Action *ActionFactoryIAS::createLedIASSetReqAction(const QByteArray &packet)
{
    PacketReader packetReader(packet);
    packetReader.skip(5);
    bool ledStatus = packetReader.readUChar();
    //qDebug() << "ActionFactoryIAS::createLedIASSetReqAction(ledStatus = " << ledStatus << ")";
    return new LedIASSetReqAction(m_ias, ledStatus);

}

Action *ActionFactoryIAS::createLedIASGetReqAction(const QByteArray &packet)
{
    //qDebug() << "ActionFactoryIAS::createLedIASGetReqAction";
    Q_UNUSED(packet)
    return new LedIASGetReqAction(m_ias, m_transmissionQueue);
}

Action *ActionFactoryIAS::createKeepaliveReqAction(const QByteArray &packet)
{
    Q_UNUSED(packet)
    //qDebug() << "ActionFactory::createKeepaliveReqAction";
    return new KeepaliveReqAction(m_transmissionQueue, m_imageDataBase);
}

Action *ActionFactoryIAS::createCaptureReqAction(const QByteArray &packet)
{
    //qDebug() << "ActionFactory::createCaptureReqAction";
    PacketReader packetReader(packet);
    packetReader.skip(SKIP_TO_PAYLOAD);
    quint8 usingWebcam = packetReader.readUChar();
    return new CaptureReqAction(m_imageManagerIAS, static_cast<bool>(usingWebcam));
}

Action *ActionFactoryIAS::createCropReqAction(const QByteArray &packet)
{
    QList<ROI> roiList;
    PacketReader packetReader(packet);
    quint8 payloadSize = packetReader.payloadSize();
    packetReader.skip(SKIP_TO_PAYLOAD);
    quint16 imageId = packetReader.readUInt16();
    quint8 crops = (payloadSize-sizeof(imageId)) / sizeof(ROI);

    for (int i = 0; i < crops; i++)
    {
        quint16 x = packetReader.readUInt16();
        quint16 y = packetReader.readUInt16();
        quint16 width = packetReader.readUInt16();
        quint16 height = packetReader.readUInt16();

        roiList.append(ROI{x, y, width, height});
    }

    return new CropReqAction(m_imageManagerIAS, imageId, roiList);
}

Action *ActionFactoryIAS::createImageHQReqAction(const QByteArray &packet)
{
    //TODO: sacar el image id a partir de los bytes del payload
    //m_imageDataBase->getImageName()
    //pasar de id a path y crear la accion
    PacketReader packetReader(packet);
    packetReader.skip(5);
    unsigned short imageId = packetReader.readUInt16();
    QString imagePath = "";
    if (m_imageDataBase)
    {
        imagePath = m_imageDataBase->getImageBasePathAndNameWithExtension(imageId, HIGH_QUALITY_EXTENSION);
    }
    return new ImageHQReqAction(m_transmissionQueue, imageId, imagePath);
}

Action *ActionFactoryIAS::createImageLQReqAction(const QByteArray &packet)
{
    //TODO: sacar el image id a partir de los bytes del payload
    //m_imageDataBase->getImageName()
    //pasar de id a path y crear la accion
    PacketReader packetReader(packet);
    packetReader.skip(5);
    unsigned short imageId = packetReader.readUInt16();
    QString imagePath = "";
    if (m_imageDataBase)
    {
        imagePath = m_imageDataBase->getImageBasePathAndNameWithExtension(imageId, LOW_QUALITY_EXTENSION);
    }
    return new ImageLQReqAction(m_transmissionQueue, imageId, imagePath);
}

Action *ActionFactoryIAS::createCatalogReqAction(const QByteArray &packet)
{
    Q_UNUSED(packet)
    return new CatalogReqAction(m_transmissionQueue ,m_imageDataBase);
}

Action *ActionFactoryIAS::createDeleteReqAction(const QByteArray &packet)
{
    PacketReader packetReader(packet);
    quint8 payloadSize = packetReader.payloadSize();
    quint8 images = payloadSize/IMAGE_ID_SIZE;
    QList<quint16> imageList;
    packetReader.skip(SKIP_TO_PAYLOAD);

    for (int i = 0; i < images; i++)
    {
        quint16 imageId = packetReader.readUInt16();
        imageList.append(imageId);
    }

    return new DeleteReqAction(m_imageDataBase, imageList);
}
