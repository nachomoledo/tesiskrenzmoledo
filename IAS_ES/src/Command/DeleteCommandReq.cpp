#include "DeleteCommandReq.h"
#include "Operators.h"

DeleteCommandReq::DeleteCommandReq(QList<quint16> imageIds)
    : m_imageIds(imageIds)
{
    for (int i = 0; i < m_imageIds.size(); i++)
    {
        m_payload << quint16(m_imageIds.at(i));
    }
}

CommandCode DeleteCommandReq::getCommandCode()
{
    return CommandCode::DELETE_REQ;
}
