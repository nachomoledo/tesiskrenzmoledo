#include "PacketReader.h"
#include <QDebug>

PacketReader::PacketReader(const QByteArray &packet)
    : m_index(0)
{
    QDataStream data(packet);
    int bytesToRead = packet.size();
    if (bytesToRead > (MAX_PACKET_SIZE-1))
    {
        bytesToRead = (MAX_PACKET_SIZE-1);
    }

    int bytesRead = data.readRawData(m_byteArray, bytesToRead);// verificar que termina en '\0'

    if (0 <= bytesRead)
    {
        m_byteArray[bytesRead] = 0x00;
    }
    else
    {
        //qDebug() << "ERROR: no se pudo leer el paquete";
    }
}

quint8 PacketReader::readUChar()
{
    int bytesToRead = 1;
    quint8 result;
    QByteArray aux(&m_byteArray[m_index], bytesToRead);
    result = aux[0];
    m_index = m_index + bytesToRead;
    return result;
}

quint16 PacketReader::readUInt16()
{
    int bytesToRead = 2;
    QByteArray aux(&m_byteArray[m_index], bytesToRead);
    quint16 result;

    QDataStream in(aux);
    in.setByteOrder(QDataStream::BigEndian);

    in >> result;
    m_index = m_index + bytesToRead;
    return result;
}

quint32 PacketReader::readUInt32()
{
    int bytesToRead = 4;
    QByteArray aux(&m_byteArray[m_index], bytesToRead);
    quint32 result;

    QDataStream in(aux);
    in.setByteOrder(QDataStream::BigEndian);

    in >> result;
    m_index = m_index + bytesToRead;
    return result;
}

quint64 PacketReader::readUInt64()
{
    int bytesToRead = 8;
    QByteArray aux(&m_byteArray[m_index], bytesToRead);
    quint64 result;

    QDataStream in(aux);
    in.setByteOrder(QDataStream::BigEndian);

    in >> result;
    m_index = m_index + bytesToRead;
    return result;
}

void PacketReader::skip(unsigned int bytes)
{
    m_index = m_index + bytes;
}

QByteArray PacketReader::getPayload()
{
    quint8 size = payloadSize();
    QByteArray aux2(&m_byteArray[5], size);
    return aux2;
}

quint8 PacketReader::payloadSize()
{
    QByteArray aux(&m_byteArray[4], 1);
    return aux[0];
}
