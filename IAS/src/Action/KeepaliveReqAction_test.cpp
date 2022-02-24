#include "KeepaliveReqAction.h"
#include "gtest/gtest.h"


class KeepaliveReqActionTest : public testing::Test
{
public:
    KeepaliveReqActionTest()
    {
        transmissionQueue = new TransmissionQueue();
        imageDataBase = new ImageDataBase("", "");
        m_keepaliveReqAction = new KeepaliveReqAction(transmissionQueue, imageDataBase);
    }

protected:
    //Class Under Test
    KeepaliveReqAction* m_keepaliveReqAction;
    // Dependencias
    TransmissionQueue *transmissionQueue;
    ImageDataBase *imageDataBase;

};

TEST_F(KeepaliveReqActionTest, functionTest)
{
    m_keepaliveReqAction->execute();
    m_keepaliveReqAction = new KeepaliveReqAction(transmissionQueue, nullptr);
    m_keepaliveReqAction->execute();
}
