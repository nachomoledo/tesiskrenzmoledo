#ifndef PACKETVALIDATOR_H
#define PACKETVALIDATOR_H
#include <QByteArray>

//quint16 qByteArrayToUInt16(QByteArray data);

#define PROTOCOL_INIT_FLAG 0x7E
#define PROTOCOL_END_FLAG 0x7D

class PacketValidator
{
    friend class PacketBuilder;
    friend class CommManager;

private:
    static quint8 getInitFlag(void);
    static quint8 getEndFlag(void);
    static quint16 getNextId(void);
    static QByteArray getPayloadLength(unsigned char lenght);
    static QByteArray getCRC();
public:
    static bool isPacketValid(const QByteArray &packet);
};



#endif // PACKETVALIDATOR_H
