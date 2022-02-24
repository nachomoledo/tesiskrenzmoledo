#include "ImageLQResAction.h"
#include "gtest/gtest.h"


class ImageLQResActionTest : public testing::Test
{
public:
    ImageLQResActionTest()
    {
        m_imageLQResAction = new ImageLQResAction("", 0, 0, {});
    }

protected:
    //Class Under Test
    ImageLQResAction* m_imageLQResAction;
    // Dependencias

};

TEST_F(ImageLQResActionTest, functionTest)
{
    m_imageLQResAction->execute();
    delete(m_imageLQResAction);
}
