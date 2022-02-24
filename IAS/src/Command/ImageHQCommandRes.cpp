#include "ImageHQCommandRes.h"
#include "Operators.h"

ImageHQCommandRes::ImageHQCommandRes(int imageId,int packetNumber, int totalPackets, QByteArray imageData)
    : m_imageId(imageId), m_packetNumber(packetNumber), m_totalPackets(totalPackets), m_imageData(imageData)
{
    m_payload << quint16(m_imageId);
    m_payload << quint32(m_packetNumber);
    m_payload << quint32(m_totalPackets);
    m_payload.append(m_imageData);
}

CommandCode ImageHQCommandRes::getCommandCode()
{
    return CommandCode::IMAGE_HQ_RES;
}
