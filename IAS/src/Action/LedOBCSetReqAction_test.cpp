#include "LedOBCSetReqAction.h"
#include "gtest/gtest.h"


class LedOBCSetReqActionTest : public testing::Test
{
public:
    LedOBCSetReqActionTest()
    {
        m_ledOBCSetReqAction = new LedOBCSetReqAction(nullptr, false);
    }

protected:
    //Class Under Test
    LedOBCSetReqAction* m_ledOBCSetReqAction;
    // Dependencias

};

TEST_F(LedOBCSetReqActionTest, functionTest)
{
    m_ledOBCSetReqAction->execute();
}
