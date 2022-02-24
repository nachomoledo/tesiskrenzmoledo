#include "ImageLQCommandReq.h"
#include "gtest/gtest.h"


class ImageLQCommandReqTest : public testing::Test
{
public:
    ImageLQCommandReqTest()
    {
        m_imageLQCommandReq = new ImageLQCommandReq(0);
    }

protected:
    //Class Under Test
    ImageLQCommandReq* m_imageLQCommandReq;
    // Dependencias

};

TEST_F(ImageLQCommandReqTest, functionTest)
{
    m_imageLQCommandReq->getCommandCode();
}
