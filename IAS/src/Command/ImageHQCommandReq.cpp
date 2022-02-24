#include "ImageHQCommandReq.h"
#include "Operators.h"
#include "Defines.h"

ImageHQCommandReq::ImageHQCommandReq(unsigned short imageId)
    : m_imageId(imageId)
{
    m_payload << quint16(m_imageId);
}

CommandCode ImageHQCommandReq::getCommandCode()
{
    return CommandCode::IMAGE_HQ_REQ;
}
