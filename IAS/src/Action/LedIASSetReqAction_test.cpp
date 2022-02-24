#include "LedIASSetReqAction.h"
#include "gtest/gtest.h"


class LedIASSetReqActionTest : public testing::Test
{
public:
    LedIASSetReqActionTest()
    {
        m_ledIASSetReqAction = new LedIASSetReqAction(ias, status);
    }

protected:
    //Class Under Test
    LedIASSetReqAction* m_ledIASSetReqAction;
    // Dependencias
    ImageAcquisitionSystem *ias = nullptr;
    bool status = false;
};

TEST_F(LedIASSetReqActionTest, functionTest)
{
    m_ledIASSetReqAction->execute();
}
