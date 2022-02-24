#ifndef PACKETBUILDER_H
#define PACKETBUILDER_H

#include "PacketValidator.h"
#include "Command.h"
#include <QByteArray>

class PacketBuilder
{
private:
    QByteArray createGenericPacket(Command *command);

public:
    PacketBuilder();
    QByteArray createPacket(Command *command);
    static quint8 invertBit5(quint8 byte);
    static quint16 encodeReservedValue(quint8 byte);
    static QByteArray addEscapeSequences(QByteArray &packet);
    QByteArray removeEscapeSequences(QByteArray &packet);
    static bool isReservedValue(quint8 value);
};

#endif // PACKETBUILDER_H
