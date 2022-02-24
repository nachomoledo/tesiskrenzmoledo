#include "CaptureReqAction.h"
#include <QDebug>

CaptureReqAction::CaptureReqAction(ImageManagerIAS *imageManagerIAS, bool usingWebcam)
    : m_imageManagerIAS(imageManagerIAS), m_usingWebcam(usingWebcam)
{

}

void CaptureReqAction::execute(void)
{
    if (!m_imageManagerIAS)
    {
        //qDebug() << "ERROR: Image Manager is not set";
        return;
    }

    m_imageManagerIAS->captureImage(m_usingWebcam);

    //qDebug() << "end CaptureReqAction::execute";
}


