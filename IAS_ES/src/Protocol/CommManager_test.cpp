#include "CommManager.h"
#include "CommLinkMonitor.h"

#include "gtest/gtest.h"
//#include <QSignalSpy>
#include <QObject>

class CommManagerTest : public testing::Test, public QObject
{
public:
    CommManagerTest()
    {
        m_actionFactory = new ActionFactory();
        m_actionManager = new ActionManager();
        m_transmissionQueue = new TransmissionQueue();
        m_commManager = new CommManager(m_transmissionQueue, m_actionFactory, m_actionManager);
        m_commLinkMonitor = new CommLinkMonitor(m_transmissionQueue);
//        m_imageDataBase = new ImageDataBase("0");
    }

protected:
    //Dependancies
    ActionFactory *m_actionFactory;
    ActionManager *m_actionManager;
    CommLinkMonitor *m_commLinkMonitor;
    //Class Under Test
    CommManager *m_commManager;
    TransmissionQueue *m_transmissionQueue;
//    ImageDataBase *m_imageDataBase;
};

TEST_F(CommManagerTest, sendKeepaliveMessage)
{
//    m_commManager->startComm();
//    m_commManager->stopComm();
    m_commManager->addPort(PortId::ES_IAS_PORT, nullptr);
    m_commManager->addPort(PortId::ES_IAS_PORT, new SerialPortManager());
    m_commManager->registerCommand(CommandCode::CAPTURE_REQ, PortId::ES_IAS_PORT);
    m_commManager->registerForwardingCommand(CommandCode::CAPTURE_REQ, PortId::ES_IAS_PORT);
    m_commManager->getSerialPortManager(PortId::ES_IAS_PORT);
//    m_commLinkMonitor->sendKeepaliveMessage();
//    ASSERT_EQ(TransmissionQueue::getInstance().count(), 1);
//    ASSERT_EQ(TransmissionQueue::getInstance().takeCommand()->getCommandCode(), CommandCode::KEEPALIVE_REQ);
}
