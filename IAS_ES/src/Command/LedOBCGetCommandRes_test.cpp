#include "LedOBCGetCommandRes.h"
#include "gtest/gtest.h"


class LedOBCGetCommandResTest : public testing::Test
{
public:
    LedOBCGetCommandResTest()
    {
        m_ledOBCGetCommandRes = new LedOBCGetCommandRes(false);
    }

protected:
    //Class Under Test
    LedOBCGetCommandRes* m_ledOBCGetCommandRes;
    // Dependencias

};

TEST_F(LedOBCGetCommandResTest, functionTest)
{
    m_ledOBCGetCommandRes->getCommandCode();
}
