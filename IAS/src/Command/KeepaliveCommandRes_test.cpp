#include "KeepaliveCommandRes.h"
#include "gtest/gtest.h"


class KeepaliveCommandResTest : public testing::Test
{
public:
    KeepaliveCommandResTest()
    {
        m_keepaliveCommandRes = new KeepaliveCommandRes({});
    }

protected:
    //Class Under Test
    KeepaliveCommandRes* m_keepaliveCommandRes;
    // Dependencias

};

TEST_F(KeepaliveCommandResTest, functionTest)
{
    m_keepaliveCommandRes->getCommandCode();
}
