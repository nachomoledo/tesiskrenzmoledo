#ifndef CAPTUREREQACTION_H
#define CAPTUREREQACTION_H

#include "Action.h"
#include "ImageManagerIAS.h"
#include "CameraManager.h"

class CaptureReqAction : public Action
{
private:
   ImageManagerIAS *m_imageManagerIAS;
   bool m_usingWebcam;
public:
    CaptureReqAction(ImageManagerIAS *imageManagerIAS, bool usingWebcam);
    void execute(void) override;
};

#endif // CAPTUREREQACTION_H
