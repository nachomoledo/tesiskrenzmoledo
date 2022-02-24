#include "CatalogCommandReq.h"
#include "gtest/gtest.h"


class CatalogCommandReqTest : public testing::Test
{
public:
    CatalogCommandReqTest()
    {
        m_catalogCommandReq = new CatalogCommandReq();
    }

protected:
    //Class Under Test
    CatalogCommandReq* m_catalogCommandReq;
    // Dependencias

};

TEST_F(CatalogCommandReqTest, functionTest)
{
    m_catalogCommandReq->getCommandCode();
}
