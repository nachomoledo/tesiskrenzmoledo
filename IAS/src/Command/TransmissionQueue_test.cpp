#include "TransmissionQueue.h"
#include "gtest/gtest.h"


class TransmissionQueueTest : public testing::Test
{
public:
    TransmissionQueueTest()
    {
        m_transmissionQueue = new TransmissionQueue();
    }

protected:
    //Class Under Test
    TransmissionQueue* m_transmissionQueue;
    // Dependencias

};

TEST_F(TransmissionQueueTest, functionTest)
{
    m_transmissionQueue->addCommand(nullptr);
    m_transmissionQueue->isEmpty();
    m_transmissionQueue->count();
    m_transmissionQueue->takeCommand();
}
