#include "KeepaliveResAction.h"
#include "gtest/gtest.h"


class KeepaliveResActionTest : public testing::Test
{
public:
    KeepaliveResActionTest()
    {
        m_transmissionQueue = new TransmissionQueue();
        m_clm = new CommLinkMonitor(m_transmissionQueue);
        m_imageDataBase = new ImageDataBase("", "");
        m_keepaliveResAction = new KeepaliveResAction(nullptr, nullptr, nullptr, {});
    }

protected:
    //Class Under Test
    KeepaliveResAction* m_keepaliveResAction;
    // Dependencias
    TransmissionQueue *m_transmissionQueue;
    CommLinkMonitor *m_clm;
    ImageDataBase *m_imageDataBase;
};

TEST_F(KeepaliveResActionTest, functionTest)
{
    m_keepaliveResAction->execute();
    delete(m_keepaliveResAction);
    m_keepaliveResAction = new KeepaliveResAction(m_transmissionQueue, m_clm, m_imageDataBase, {});
    m_keepaliveResAction->execute();
    delete(m_keepaliveResAction);
}
