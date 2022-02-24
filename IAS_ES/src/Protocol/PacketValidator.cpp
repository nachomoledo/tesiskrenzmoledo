#include "PacketValidator.h"
#include "CommandCode.h"
#include <QDataStream>
#include <QDebug>
#include "Operators.h"

quint8 PacketValidator::getInitFlag(void)
{
    return PROTOCOL_INIT_FLAG;
}

quint8 PacketValidator::getEndFlag(void)
{
    return PROTOCOL_END_FLAG;
}

quint16 PacketValidator::getNextId(void)
{
    static unsigned short id = 0;
    return id++;
}

//TODO: VERIFICAR FIN DEL PACKET
bool PacketValidator::isPacketValid(const QByteArray &packet)
{
    bool okCommand = false;
    bool retValue = false;
    //qDebug() << "PacketValidator::isPacketValid";
    if (packet.isEmpty())
    {
        //qDebug() << "ERROR: empty packet";
        return retValue;
    }

    if (packet.at(0) != PacketValidator::getInitFlag())
    {
        //qDebug() << "ERROR: invalid init flag: " << packet.at(0);
        return retValue;
    }

    //fixme: esto esta mal, los comandos no estan seguidos, hacer switch case de ultima

    if (packet.size() > 3)
    {
        for (int i = 0; i < static_cast<int>(CommandCode::N_COMMANDS); i++)
        {
            if ((quint8) packet.at(3) == i)
            {
                okCommand = true;
                break;
            }
        }
        if (false == okCommand)
        {
            //qDebug() << "ERROR: invalid command: " << (quint8) packet.at(3) << ", packet = " << packet;

            return retValue;
        }
    }
    else
    {
        //qDebug() << "ERROR: invalid command size: " << packet.size() << ", packet = " << packet;
        return retValue;
    }



    retValue = true;
    return retValue;
}

