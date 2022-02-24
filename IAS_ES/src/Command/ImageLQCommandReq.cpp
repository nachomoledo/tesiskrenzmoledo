#include "ImageLQCommandReq.h"
#include "Operators.h"

ImageLQCommandReq::ImageLQCommandReq(unsigned short imageId)
    : m_imageId(imageId)
{
    m_payload << quint16(m_imageId);
}

CommandCode ImageLQCommandReq::getCommandCode()
{
    return CommandCode::IMAGE_LQ_REQ;
}
