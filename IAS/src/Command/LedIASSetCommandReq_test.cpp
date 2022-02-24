#include "LedIASSetCommandReq.h"
#include "gtest/gtest.h"


class LedIASSetCommandReqTest : public testing::Test
{
public:
    LedIASSetCommandReqTest()
    {
        m_ledIASSetCommandReq = new LedIASSetCommandReq(false);
    }

protected:
    //Class Under Test
    LedIASSetCommandReq* m_ledIASSetCommandReq;
    // Dependencias

};

TEST_F(LedIASSetCommandReqTest, functionTest)
{
    m_ledIASSetCommandReq->getCommandCode();
}
