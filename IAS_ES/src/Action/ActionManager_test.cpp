#include "ActionManager.h"
#include "gtest/gtest.h"
#include "LedOBCSetReqAction.h"

class ActionManagerTest : public testing::Test
{
public:
    ActionManagerTest()
    {
        m_actionManager = new ActionManager();
    }

protected:
    //Class Under Test
    ActionManager* m_actionManager;
    // Dependencias

};

TEST_F(ActionManagerTest, functionTest)
{
    m_actionManager->addAction(new LedOBCSetReqAction(nullptr, false));
    m_actionManager->addAction(new LedOBCSetReqAction(nullptr, false));
}
