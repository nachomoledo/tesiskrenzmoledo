#include "LedOBCGetCommandReq.h"
#include "gtest/gtest.h"


class LedOBCGetCommandReqTest : public testing::Test
{
public:
    LedOBCGetCommandReqTest()
    {
        m_ledOBCGetCommandReq = new LedOBCGetCommandReq();
    }

protected:
    //Class Under Test
    LedOBCGetCommandReq* m_ledOBCGetCommandReq;
    // Dependencias

};

TEST_F(LedOBCGetCommandReqTest, functionTest)
{
    m_ledOBCGetCommandReq->getCommandCode();
}
