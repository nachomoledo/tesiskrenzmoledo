#include "KeepaliveReqAction.h"
#include "KeepaliveCommandRes.h"
#include <QDebug>

KeepaliveReqAction::KeepaliveReqAction(TransmissionQueue *transmissionQueue, ImageDataBase *imageDB)
    : m_transmissionQueue(transmissionQueue), m_imageDataBase(imageDB)
{

}

void KeepaliveReqAction::execute()
{
    //qDebug() << "KeepaliveReqAction::execute()";
    if (m_transmissionQueue && m_imageDataBase)
    {
        m_transmissionQueue->addCommand(new KeepaliveCommandRes(m_imageDataBase->getLastChecksum()));
    }
}
