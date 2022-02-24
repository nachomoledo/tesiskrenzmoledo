#include "CaptureReqAction.h"
#include "gtest/gtest.h"


class CaptureReqActionTest : public testing::Test
{
public:
    CaptureReqActionTest()
    {
        transmissionQueue = new TransmissionQueue();
        imageManagerIAS = new ImageManagerIAS(transmissionQueue);
        m_CaptureReqAction = new CaptureReqAction(imageManagerIAS, false);
    }

protected:
    //Class Under Test
    CaptureReqAction* m_CaptureReqAction;
    // Dependencias
    ImageManagerIAS *imageManagerIAS;
    TransmissionQueue *transmissionQueue;
};

TEST_F(CaptureReqActionTest, functionTest)
{
    m_CaptureReqAction->execute();
    delete(m_CaptureReqAction);
    m_CaptureReqAction = new CaptureReqAction(nullptr, false);
    m_CaptureReqAction->execute();
}
