#include "ImageHQCommandRes.h"
#include "gtest/gtest.h"


class ImageHQCommandResTest : public testing::Test
{
public:
    ImageHQCommandResTest()
    {
        m_imageHQCommandRes = new  ImageHQCommandRes(0, 0, 0, {});
    }

protected:
    //Class Under Test
    ImageHQCommandRes* m_imageHQCommandRes;
    // Dependencias

};

TEST_F(ImageHQCommandResTest, functionTest)
{
    m_imageHQCommandRes->getCommandCode();
}
