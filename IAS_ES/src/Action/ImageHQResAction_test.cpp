#include "ImageHQResAction.h"
#include "gtest/gtest.h"


class ImageHQResActionTest : public testing::Test
{
public:
    ImageHQResActionTest()
    {
        m_imageHQResAction = new ImageHQResAction("", 0, 0, {});
    }

protected:
    //Class Under Test
    ImageHQResAction* m_imageHQResAction;
    // Dependencias

};

TEST_F(ImageHQResActionTest, functionTest)
{
    /* FIXME: MUCHOS PRINTS TransmissionQueue::addCommand: emit commandAdded()*/
    m_imageHQResAction->execute();
    delete(m_imageHQResAction);
}
