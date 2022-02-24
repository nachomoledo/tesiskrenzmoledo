#ifndef CATALOGRESACTION_H
#define CATALOGRESACTION_H

#include "Action.h"
#include "ImageDataBase.h"
#include "ImageProperties.h"

class CatalogResAction : public Action
{
private:
    ImageDataBase *m_imageDataBase;
    unsigned short m_id;
    ImageProperties *m_imageProperties;
    unsigned short m_packetNumber;
    unsigned short m_totalPackets;

public:
    CatalogResAction(ImageDataBase *dataBase, unsigned short id, ImageProperties *imageProperties, unsigned short packetNumber, unsigned short totalPackets);
    void execute(void) override;
};

#endif // CATALOGRESACTION_H
