#include "LedOBCGetReqAction.h"
#include "gtest/gtest.h"


class LedOBCGetReqActionTest : public testing::Test
{
public:
    LedOBCGetReqActionTest()
    {
        m_ledOBCGetReqAction = new LedOBCGetReqAction(nullptr, nullptr);
    }

protected:
    //Class Under Test
    LedOBCGetReqAction* m_ledOBCGetReqAction;
    // Dependencias

};

TEST_F(LedOBCGetReqActionTest, functionTest)
{
    m_ledOBCGetReqAction->execute();
}
