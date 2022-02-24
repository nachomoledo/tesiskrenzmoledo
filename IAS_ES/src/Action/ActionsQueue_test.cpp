#include "ActionsQueue.h"
#include "gtest/gtest.h"
#include "LedOBCSetReqAction.h"

class ActionsQueueTest : public testing::Test
{
public:
    ActionsQueueTest()
    {
        m_ActionsQueue = new ActionsQueue();
    }

protected:
    //Class Under Test
    ActionsQueue* m_ActionsQueue;
    // Dependencias

};

TEST_F(ActionsQueueTest, functionTest)
{
    m_ActionsQueue->isEmpty();
    m_ActionsQueue->takeAction();
    m_ActionsQueue->addAction(nullptr);
    m_ActionsQueue->addAction(new LedOBCSetReqAction(nullptr, false));
    m_ActionsQueue->isEmpty();
    m_ActionsQueue->takeAction();
}
