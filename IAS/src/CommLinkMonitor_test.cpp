#include "CommLinkMonitor.h"
#include "CommManager.h"

#include "gtest/gtest.h"
//#include <QSignalSpy>
#include <QObject>

class CommLinkMonitorTest : public testing::Test, public QObject
{
public:
    CommLinkMonitorTest()
    {
        m_actionFactory = new ActionFactory();
        m_actionManager = new ActionManager();
        m_transmissionQueue = new TransmissionQueue();
        m_commManager = new CommManager(m_transmissionQueue, m_actionFactory, m_actionManager);
        m_commLinkMonitor = new CommLinkMonitor(m_transmissionQueue);
    }

protected:
    //Class Under Test
    CommLinkMonitor* m_commLinkMonitor;
    //Dependencies
    ActionFactory *m_actionFactory;
    ActionManager *m_actionManager;
    CommManager* m_commManager;
    TransmissionQueue *m_transmissionQueue;
};

TEST_F(CommLinkMonitorTest, sendKeepaliveMessage)
{
    m_commLinkMonitor->start();
    m_commLinkMonitor->stop();
    m_commLinkMonitor->isActive();
    m_commLinkMonitor->resetCounter();
    m_commLinkMonitor->sendKeepaliveMessage();
    m_commLinkMonitor->getAutoUpdate();
    m_commLinkMonitor->setAutoUpdate(true);
    m_commLinkMonitor->setAutoUpdate(false);
    m_commLinkMonitor->getCommStatus();
//    m_commLinkMonitor->sendKeepaliveMessage();
//    ASSERT_EQ(TransmissionQueue::getInstance().count(), 1);
//    ASSERT_EQ(TransmissionQueue::getInstance().takeCommand()->getCommandCode(), CommandCode::KEEPALIVE_REQ);


}
