#include "ImageHQReqAction.h"
#include "gtest/gtest.h"


class ImageHQReqActionTest : public testing::Test
{
public:
    ImageHQReqActionTest()
    {
        m_transmissionQueue = new TransmissionQueue();
        m_imageHQReqAction = new ImageHQReqAction(nullptr, 0, "");
    }

protected:
    //Class Under Test
    ImageHQReqAction* m_imageHQReqAction;
    // Dependencias
    TransmissionQueue *m_transmissionQueue;
};

TEST_F(ImageHQReqActionTest, functionTest)
{
    m_imageHQReqAction->execute();
    delete(m_imageHQReqAction);
    m_imageHQReqAction = new ImageHQReqAction(m_transmissionQueue, 0, "");
    m_imageHQReqAction->execute();
    delete(m_imageHQReqAction);
    /* FIXME: se atora al agregar comandos a la cola */
//    m_imageHQReqAction = new ImageHQReqAction(m_transmissionQueue, 0, "/home/tesis/Repos/TESIS_V2/res/image.jpg");
//    m_imageHQReqAction->execute();
//    delete(m_imageHQReqAction);
}
