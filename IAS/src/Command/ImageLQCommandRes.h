#ifndef IMAGELQRESPONSECOMMAND_H
#define IMAGELQRESPONSECOMMAND_H

#include "Command.h"
#include <QString>
#include <QByteArray>

#define PKT_DATA_MAX 120 //FIXME: multiplo de pixel? mandar primero paquete con metadata?

class ImageLQCommandRes : public Command
{
private:
    int m_imageId;
    int m_packetNumber;
    int m_totalPackets;
    QByteArray m_imageData;

public:
    //FIXME: IMAGE ID DE 16!
    ImageLQCommandRes(int imageId,int packetNumber, int totalPackets, QByteArray imageData);
    CommandCode getCommandCode(void) override;
};

#endif // GETIMAGERESPONSECOMMAND_H
