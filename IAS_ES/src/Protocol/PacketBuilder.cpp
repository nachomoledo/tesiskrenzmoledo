#include "PacketBuilder.h"
#include "Operators.h"
#include <QList>
#include <ImageHQCommandRes.h>
#include <ImageHQCommandReq.h>
#include <QDebug>

PacketBuilder::PacketBuilder()
{

}

quint8 PacketBuilder::invertBit5(quint8 byte)
{
    return  byte ^ 0x20;
}

quint16 PacketBuilder::encodeReservedValue(quint8 byte)
{
    quint8 inverted = invertBit5(byte);
    return quint16(inverted | (0x7D << 8));
}

bool PacketBuilder::isReservedValue(quint8 value)
{
    bool retValue = false;
    switch (value) {
    case PROTOCOL_INIT_FLAG:
        retValue = true;
        break;
    case PROTOCOL_END_FLAG:
        retValue = true;
        break;
    default:
        break;
    }
    return  retValue;
}

QByteArray PacketBuilder::addEscapeSequences(QByteArray &packet)
{
    int packetSize = packet.size();
    for (int i = 1; i < packetSize; i++)
    {
        if (isReservedValue(packet.at(i)) && (i < packetSize-1))
        {
            QByteArray aux;
            aux << quint16(encodeReservedValue(packet.at(i)));
            packet.replace(i, 1, aux);
            packetSize++;
        }
    }
    return packet;
}

QByteArray PacketBuilder::removeEscapeSequences(QByteArray &packet)
{
    int packetSize = packet.size();
    //qDebug() << "packetSize = " << packetSize;

    for (int i = 0; i < packetSize; i++)
    {
        //qDebug() << "i = " << i;
        if ((PROTOCOL_END_FLAG == packet.at(i)) && (i < packetSize-1))
        {
            quint8 auxByte = invertBit5(packet.at(i+1));
            QByteArray aux;
            aux << quint8(auxByte);
            packet.replace(i, 2, aux);
            packetSize = packet.size();
            //qDebug() << "packetSize = " << packetSize;
        }
    }
    return packet;
}

//FIXME: agregar CRC
//FIXME: paquete especial cuando aparece secuencia de inicio o finalización en el payload
//FIXME: Agregar el método getPayload a los commands que faltan para solo usar createGenericPacket
QByteArray PacketBuilder::createPacket(Command *command)
{
    return createGenericPacket(command);
}

QByteArray PacketBuilder::createGenericPacket(Command *command)
{
    QByteArray data;

    if (command)
    {
        data << quint8(PacketValidator::getInitFlag());
        data << quint8(0xFF);
        data << quint8(0xFF);
//        data << quint16(PacketValidator::getNextId());
        data << quint8(command->getCommandCode());
        data << quint8(command->getPayload().size());
        data.append(command->getPayload());
        int crc = 0;
        data.append(crc);
        data << quint8(PacketValidator::getEndFlag());
    }
    return data;
}
