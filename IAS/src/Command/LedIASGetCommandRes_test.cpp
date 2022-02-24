#include "LedIASGetCommandRes.h"
#include "gtest/gtest.h"


class LedIASGetCommandResTest : public testing::Test
{
public:
    LedIASGetCommandResTest()
    {
        m_ledIASGetCommandRes = new LedIASGetCommandRes(status);
    }

protected:
    //Class Under Test
    LedIASGetCommandRes* m_ledIASGetCommandRes;
    // Dependencias
    bool status = false;
};

TEST_F(LedIASGetCommandResTest, functionTest)
{
    m_ledIASGetCommandRes->getCommandCode();
    m_ledIASGetCommandRes->getPayload();
}
