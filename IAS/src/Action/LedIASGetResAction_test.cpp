#include "LedIASGetResAction.h"
#include "gtest/gtest.h"


class LedIASGetResActionTest : public testing::Test
{
public:
    LedIASGetResActionTest()
    {
        m_ledIASGetResAction = new LedIASGetResAction(nullptr, false);
    }

protected:
    //Class Under Test
    LedIASGetResAction* m_ledIASGetResAction;
    // Dependencias

};

TEST_F(LedIASGetResActionTest, functionTest)
{
    m_ledIASGetResAction->execute();
}
