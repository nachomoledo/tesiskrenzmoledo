#include "ActionFactoryES.h"
#include "KeepaliveResAction.h"
#include "ImageHQResAction.h"
#include "ImageLQResAction.h"
#include "CatalogResAction.h"
#include "LedIASGetResAction.h"
#include "LedOBCGetResAction.h"
#include "PacketReader.h"
#include "Defines.h"
#include <QList>
#include <QDebug>

ActionFactoryES::ActionFactoryES(EarthStation *earthStation, TransmissionQueue *transmissionQueue, CommLinkMonitor *clm, ImageDataBase *imgDataBase, ImageManager *imageManager)
    : ActionFactory(), m_earthStation(earthStation), m_transmissionQueue(transmissionQueue), m_commLinkMonitor(clm), m_imageDataBase(imgDataBase), m_imageManager(imageManager)
{    
    registerCreateActionFn(static_cast<quint8>(CommandCode::KEEPALIVE_RES), [=](const QByteArray &packet) { return this->createKeepaliveResAction(packet);});
    registerCreateActionFn(static_cast<quint8>(CommandCode::IMAGE_HQ_RES), [=](const QByteArray &packet) { return this->createImageHQResAction(packet);});
    registerCreateActionFn(static_cast<quint8>(CommandCode::IMAGE_LQ_RES), [=](const QByteArray &packet) { return this->createImageLQResAction(packet);});
    registerCreateActionFn(static_cast<quint8>(CommandCode::CATALOG_RES), [=](const QByteArray &packet) { return this->createCatalogResAction(packet);});
    registerCreateActionFn(static_cast<quint8>(CommandCode::LED_IAS_GET_RES), [=](const QByteArray &packet) { return this->createLedIASGetResAction(packet);});
    registerCreateActionFn(static_cast<quint8>(CommandCode::LED_OBC_GET_RES), [=](const QByteArray &packet) { return this->createLedOBCGetResAction(packet);});
}

Action *ActionFactoryES::createKeepaliveResAction(const QByteArray &packet)
{
    PacketReader packetReader(packet);
    QByteArray catalogChecksum;
    packetReader.skip(SKIP_TO_PAYLOAD);
    catalogChecksum = packetReader.getPayload();
    return new KeepaliveResAction(m_transmissionQueue, m_commLinkMonitor, m_imageDataBase, catalogChecksum);
}

Action *ActionFactoryES::createImageHQResAction(const QByteArray &packet)
{
    //qDebug() << "createImageHQResAction = " << packet.toHex();
    PacketReader packetReader(packet);
    quint8 payloadSize = packetReader.payloadSize();
    //qDebug() << "payloadSize = " <<  payloadSize;
    //qDebug() << "getPayload = " <<  packetReader.getPayload().toHex();
    QByteArray imageData = packetReader.getPayload().right(payloadSize-10);
    packetReader.skip(5);
    quint16 imageId = packetReader.readUInt16();
    quint32 currentPacket = packetReader.readUInt32();
    quint32 totalPackets = packetReader.readUInt32();

    //    QByteArray payload = packet.right(packet.size()-(3*4));
//    payload.truncate(packet.size()-(2*4));
//    int imageId = payload.chopped(4).toInt();
//    payload = payload.right(payload.size()-4);
//    int packetNumber = payload.chopped(4).toInt();
//    payload = payload.right(payload.size()-4);
//    int totalPackets = payload.chopped(4).toInt();
//    payload = payload.right(payload.size()-4);
//    QByteArray imageData = payload;
    QString imagePath = "";
    if (m_imageDataBase)
    {
        imagePath = QString("%1%2").arg(m_imageDataBase->getImageHQPath()).arg(imageId);
        //qDebug() << "ActionFactory::createImageHQResAction if (m_imageDataBase) imagePath = |" << imagePath << "|";
    }

    return new ImageHQResAction(imagePath, currentPacket, totalPackets, imageData);
}

Action *ActionFactoryES::createImageLQResAction(const QByteArray &packet)
{
    //qDebug() << "createImageLQResAction = " << packet.toHex();
    PacketReader packetReader(packet);
    quint8 payloadSize = packetReader.payloadSize();
    //qDebug() << "payloadSize = " <<  payloadSize;
    //qDebug() << "getPayload = " <<  packetReader.getPayload().toHex();
    QByteArray imageData = packetReader.getPayload().right(payloadSize-10);
    packetReader.skip(5);
    quint16 imageId = packetReader.readUInt16();
    quint32 currentPacket = packetReader.readUInt32();
    quint32 totalPackets = packetReader.readUInt32();

    //    QByteArray payload = packet.right(packet.size()-(3*4));
//    payload.truncate(packet.size()-(2*4));
//    int imageId = payload.chopped(4).toInt();
//    payload = payload.right(payload.size()-4);
//    int packetNumber = payload.chopped(4).toInt();
//    payload = payload.right(payload.size()-4);
//    int totalPackets = payload.chopped(4).toInt();
//    payload = payload.right(payload.size()-4);
//    QByteArray imageData = payload;
    QString imagePath = "";
    if (m_imageDataBase)
    {
        //qDebug() << "ActionFactory::createImageLQResAction if (m_imageDataBase) imagePath = |" << imagePath << "|";
        imagePath = QString("%1%2").arg(m_imageDataBase->getImageLQPath()).arg(imageId);
    }

    return new ImageLQResAction(imagePath, currentPacket, totalPackets, imageData);
}

Action *ActionFactoryES::createLedIASGetResAction(const QByteArray &packet)
{
    PacketReader pr(packet);
    pr.skip(SKIP_TO_PAYLOAD);
    quint8 state = pr.readUChar();
    return new LedIASGetResAction(m_earthStation, static_cast<bool>(state));
}

Action *ActionFactoryES::createLedOBCGetResAction(const QByteArray &packet)
{
    PacketReader pr(packet);
    pr.skip(SKIP_TO_PAYLOAD);
    quint8 state = pr.readUChar();
    return new LedOBCGetResAction(m_earthStation, static_cast<bool>(state));
}

Action *ActionFactoryES::createCatalogResAction(const QByteArray &packet)
{
    PacketReader pr(packet);
    pr.skip(SKIP_TO_PAYLOAD);
    quint16 id = pr.readUInt16();
    quint16 packetNumber = pr.readUInt16();
    quint16 totalPackets = pr.readUInt16();
    quint64 size = pr.readUInt64();
    quint16 width = pr.readUInt16();
    quint16 height = pr.readUInt16();
    quint64 timestamp = pr.readUInt64();
    return new CatalogResAction(m_imageDataBase, id, new ImageProperties(id, QString::number(size), QString::number(width), QString::number(height), timestamp), packetNumber, totalPackets);
}
