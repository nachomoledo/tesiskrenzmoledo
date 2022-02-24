#ifndef PACKETREADER_H
#define PACKETREADER_H

#include <QByteArray>
#include <QDataStream>

#define MAX_PACKET_SIZE 255
#define SKIP_TO_PAYLOAD 5

class PacketReader
{
    int m_size;
    char m_byteArray[MAX_PACKET_SIZE];
    unsigned int m_index;

public:
    PacketReader(const QByteArray &packet);
    quint8 readUChar();
    quint16 readUInt16();
    quint32 readUInt32();
    quint64 readUInt64();
    void skip(unsigned int bytes);
    QByteArray getPayload();
    quint8 payloadSize();
};

#endif // PACKETREADER_H
