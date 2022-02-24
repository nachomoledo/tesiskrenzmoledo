#include "KeepaliveResAction.h"
#include "CatalogCommandReq.h"
#include <QDebug>

KeepaliveResAction::KeepaliveResAction(TransmissionQueue *transmissionQueue, CommLinkMonitor *clm, ImageDataBase *imageDataBase, QByteArray catalogChecksum)
    : m_transmissionQueue(transmissionQueue), m_commLinkMonitor(clm), m_imageDataBase(imageDataBase), m_catalogChecksum(catalogChecksum)
{

}

void KeepaliveResAction::execute()
{
    //qDebug() << "KeepaliveResAction::execute()";
    bool isCatalogUpdated = false;
    if (m_commLinkMonitor)
    {
        ////qDebug() << "m_commLinkMonitor == true";

        m_commLinkMonitor->resetCounter();

        if (m_imageDataBase)
        {
            //qDebug() << "ES checksum = " << m_imageDataBase->getLastChecksum() << " (size = " << m_imageDataBase->getLastChecksum().size() << ")";
            //qDebug() << "IAS checksum = " << m_catalogChecksum << " (size = " << m_catalogChecksum.size() << ")";
            isCatalogUpdated = (m_imageDataBase->getLastChecksum() == m_catalogChecksum);
            if (isCatalogUpdated)
            {
                //qDebug() << "catalogo actualizado!!";
            }
            else
            {
                // TODO: mostrar esta condicicón en pantalla
                //qDebug() << "catalogo necesita actualización!!";
            }
        }

        if ((false == isCatalogUpdated) && (true == m_commLinkMonitor->getAutoUpdate()) && m_transmissionQueue)
        {
            //qDebug() << "Se pide actualización de catálogo automáticamente";
            m_imageDataBase->clearImageMapAux();
            m_transmissionQueue->addCommand(new CatalogCommandReq());
        }
    }
}
