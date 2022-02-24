#include "CatalogCommandRes.h"
#include "gtest/gtest.h"


class CatalogCommandResTest : public testing::Test
{
public:
    CatalogCommandResTest()
    {
        m_catalogCommandRes = new CatalogCommandRes(0, imageProperties, 0, 0);
    }

protected:
    //Class Under Test
    CatalogCommandRes* m_catalogCommandRes;
    // Dependencias
    ImageProperties imageProperties = ImageProperties(0, "", "", "", 0);
};

TEST_F(CatalogCommandResTest, functionTest)
{
    m_catalogCommandRes->getCommandCode();
}
