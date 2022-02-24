#include "ImageProperties.h"
#include "gtest/gtest.h"


class ImagePropertiesTest : public testing::Test
{
public:
    ImagePropertiesTest()
    {
        m_imageProperties = new ImageProperties(0, "", "", "", 0);
    }

protected:
    //Class Under Test
    ImageProperties* m_imageProperties;
    // Dependencias

};

TEST_F(ImagePropertiesTest, functionTest)
{
    m_imageProperties->getPropertiesQS();
}
