#ifndef DELETEREQACTION_H
#define DELETEREQACTION_H

#include "Action.h"
#include "ImageDataBase.h"

class DeleteReqAction : public Action
{
private:
   ImageDataBase *m_imageDataBase;
   QList<quint16> m_imageList;
public:
    DeleteReqAction(ImageDataBase *imageDataBase, QList<quint16> imageList);
    void execute(void) override;
};

#endif // DELETEREQACTION_H
