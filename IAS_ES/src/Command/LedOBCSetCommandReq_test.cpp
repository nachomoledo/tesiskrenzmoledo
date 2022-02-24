#include "LedOBCSetCommandReq.h"
#include "gtest/gtest.h"


class LedOBCSetCommandReqTest : public testing::Test
{
public:
    LedOBCSetCommandReqTest()
    {
        m_ledOBCSetCommandReq = new LedOBCSetCommandReq(false);
    }

protected:
    //Class Under Test
    LedOBCSetCommandReq* m_ledOBCSetCommandReq;
    // Dependencias

};

TEST_F(LedOBCSetCommandReqTest, functionTest)
{
    m_ledOBCSetCommandReq->getCommandCode();
}
