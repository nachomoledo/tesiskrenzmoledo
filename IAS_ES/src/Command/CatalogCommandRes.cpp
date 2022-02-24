#include "CatalogCommandRes.h"
#include "Operators.h"

CatalogCommandRes::CatalogCommandRes(unsigned short id, ImageProperties &imageProperties, unsigned short packetNumber, unsigned short totalPackets)
    : m_id(id), m_imageProperties(imageProperties), m_packetNumber(packetNumber), m_totalPackets(totalPackets)
{
    m_payload << quint16(m_id);
    m_payload << quint16(m_packetNumber);
    m_payload << quint16(m_totalPackets);
    m_payload.append(m_imageProperties.getPropertiesQBA());
}

CommandCode CatalogCommandRes::getCommandCode()
{
    return CommandCode::CATALOG_RES;
}
