#include "LedIASGetCommandReq.h"
#include "gtest/gtest.h"


class LedIASGetCommandReqTest : public testing::Test
{
public:
    LedIASGetCommandReqTest()
    {
        m_ledIASGetCommandReq = new LedIASGetCommandReq();
    }

protected:
    //Class Under Test
    LedIASGetCommandReq* m_ledIASGetCommandReq;
    // Dependencias

};

TEST_F(LedIASGetCommandReqTest, functionTest)
{
    m_ledIASGetCommandReq->getCommandCode();
}
