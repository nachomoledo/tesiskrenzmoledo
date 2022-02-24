#include "ImageLQCommandRes.h"
#include "gtest/gtest.h"


class ImageLQCommandResTest : public testing::Test
{
public:
    ImageLQCommandResTest()
    {
        m_imageLQCommandRes = new ImageLQCommandRes(0, 0, 0, {});
    }

protected:
    //Class Under Test
    ImageLQCommandRes* m_imageLQCommandRes;
    // Dependencias

};

TEST_F(ImageLQCommandResTest, functionTest)
{
    m_imageLQCommandRes->getCommandCode();
}
