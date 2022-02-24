#include "CaptureCommandReq.h"
#include "Operators.h"

CaptureCommandReq::CaptureCommandReq(bool usingWebcam)
    : m_usingWebcam(usingWebcam)
{
    m_payload << static_cast<uint8_t>(usingWebcam);
}

CommandCode CaptureCommandReq::getCommandCode()
{
    return CommandCode::CAPTURE_REQ;
}
