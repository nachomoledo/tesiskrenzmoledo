#include "CatalogResAction.h"
#include <QDebug>

CatalogResAction::CatalogResAction(ImageDataBase *dataBase, unsigned short id, ImageProperties *imageProperties, unsigned short packetNumber, unsigned short totalPackets)
    : m_imageDataBase(dataBase), m_id(id), m_imageProperties(imageProperties), m_packetNumber(packetNumber), m_totalPackets(totalPackets)
{

}

void CatalogResAction::execute()
{
    //qDebug() << "CatalogResAction::execute()";
//    //qDebug() << "Id: " << m_id << ", " << m_imageProperties.getPropertiesQS();
    if (m_imageDataBase && m_imageProperties)
    {
        m_imageDataBase->buildCatalogET(m_id, m_imageProperties->getSize(), m_imageProperties->getWidth(), m_imageProperties->getHeight(), m_imageProperties->getTimestamp(), m_packetNumber, m_totalPackets);
    }
}
