#ifndef CAPTURECOMMANDREQ_H
#define CAPTURECOMMANDREQ_H

#include "Command.h"

class CaptureCommandReq : public Command
{
private:
    bool m_usingWebcam;
public:
    CaptureCommandReq(bool usingWebcam);
    CommandCode getCommandCode(void) override;
};

#endif // CAPTURECOMMANDREQ_H
