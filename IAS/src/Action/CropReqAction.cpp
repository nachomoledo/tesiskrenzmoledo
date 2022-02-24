#include "CropReqAction.h"
#include "Defines.h"
#include <QDebug>

CropReqAction::CropReqAction(ImageManagerIAS *imageManagerIAS, quint16 imageId, QList<ROI> roiList)
    : m_imageManagerIAS(imageManagerIAS), m_imageId(imageId), m_roiList(roiList)
{

}

void CropReqAction::execute(void)
{
    //qDebug() << "begin CropReqAction::execute";
    if (!m_imageManagerIAS)
    {
        //qDebug() << "ERROR: Image Manager is not set";
        return;
    }
    m_imageManagerIAS->cropImage(m_imageId, m_roiList);
    //qDebug() << "end CropReqAction::execute";
}
