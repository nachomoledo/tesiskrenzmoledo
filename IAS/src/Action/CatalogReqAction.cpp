#include "CatalogReqAction.h"
#include "CatalogCommandRes.h"
#include <QDebug>

CatalogReqAction::CatalogReqAction(TransmissionQueue *transmissionQueue, ImageDataBase *dataBase)
    : m_transmissionQueue(transmissionQueue), m_imageDataBase(dataBase)
{

}

void CatalogReqAction::execute()
{
    //qDebug() << "CatalogReqAction::execute()";
/*
* Iterar en la DB todas las imagenes y mandar comandos con sus id y propiedades
*
*/
    if (m_imageDataBase && m_transmissionQueue)
    {
        int mapSize = m_imageDataBase->getImageMap().size();
        int n = 1;
        QMapIterator<unsigned short, ImageProperties*> i(m_imageDataBase->getImageMap());
        while (i.hasNext()) {
            i.next();
            m_transmissionQueue->addCommand(new CatalogCommandRes(i.key(), *i.value(), n, mapSize));
            n++;
        }
    }
}
