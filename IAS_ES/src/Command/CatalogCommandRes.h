#ifndef CATALOGCOMMANDRES_H
#define CATALOGCOMMANDRES_H

#include "Command.h"
#include "ImageProperties.h"

class CatalogCommandRes : public Command
{
private:
    unsigned short m_id;
    ImageProperties m_imageProperties;
    int m_packetNumber;
    int m_totalPackets;
public:
    CatalogCommandRes(unsigned short id, ImageProperties &imageProperties, unsigned short packetNumber, unsigned short totalPackets);
    CommandCode getCommandCode(void) override;
};

#endif // CATALOGCOMMANDRES_H
