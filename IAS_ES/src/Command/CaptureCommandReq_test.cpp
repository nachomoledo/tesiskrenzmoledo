#include "CaptureCommandReq.h"
#include "gtest/gtest.h"


class CaptureCommandReqTest : public testing::Test
{
public:
    CaptureCommandReqTest()
    {
        m_captureCommandReq = new CaptureCommandReq(false);
    }

protected:
    //Class Under Test
    CaptureCommandReq* m_captureCommandReq;
    // Dependencias

};

TEST_F(CaptureCommandReqTest, functionTest)
{
    m_captureCommandReq->getCommandCode();
}
