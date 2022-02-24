#include "CropCommandReq.h"
#include "Operators.h"

CropCommandReq::CropCommandReq(quint16 id, QList<ROI> roiList)
    : m_imageId(id), m_roiList(roiList)
{
    m_payload << quint16(m_imageId);
    for (int i = 0; i < m_roiList.size(); i++)
    {
        ROI roi = m_roiList.at(i);
        m_payload << quint16(roi.x);
        m_payload << quint16(roi.y);
        m_payload << quint16(roi.width);
        m_payload << quint16(roi.height);
    }
}

QList<ROI> CropCommandReq::getRoiList() const
{
    return m_roiList;
}

CommandCode CropCommandReq::getCommandCode()
{
    return CommandCode::CROP_REQ;
}
