#ifndef CATALOGREQACTION_H
#define CATALOGREQACTION_H

#include "Action.h"
#include "TransmissionQueue.h"
#include "ImageDataBase.h"

class CatalogReqAction : public Action
{
private:
    TransmissionQueue *m_transmissionQueue;
    ImageDataBase *m_imageDataBase;
public:
    CatalogReqAction(TransmissionQueue *transmissionQueue, ImageDataBase *dataBase);
    void execute(void) override;
};

#endif // CATALOGREQACTION_H
