#include "LedIASGetReqAction.h"
#include "gtest/gtest.h"


class LedIASGetReqActionTest : public testing::Test
{
public:
    LedIASGetReqActionTest()
    {
        m_ledIASGetReqAction = new LedIASGetReqAction(m_ias, m_transmissionQueue);
    }

protected:
    //Class Under Test
    LedIASGetReqAction* m_ledIASGetReqAction;
    // Dependencias
    ImageAcquisitionSystem *m_ias = nullptr;
    TransmissionQueue *m_transmissionQueue = nullptr;
};

TEST_F(LedIASGetReqActionTest, functionTest)
{
    m_ledIASGetReqAction->execute();
}
