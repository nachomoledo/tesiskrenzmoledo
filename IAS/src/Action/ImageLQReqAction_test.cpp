#include "ImageLQReqAction.h"
#include "gtest/gtest.h"


class ImageLQReqActionTest : public testing::Test
{
public:
    ImageLQReqActionTest()
    {
        m_transmissionQueue = new TransmissionQueue();
        m_imageLQReqAction = new ImageLQReqAction(nullptr, 0, "");
    }

protected:
    //Class Under Test
    ImageLQReqAction* m_imageLQReqAction;
    // Dependencias
    TransmissionQueue *m_transmissionQueue;
};

TEST_F(ImageLQReqActionTest, functionTest)
{
    m_imageLQReqAction->execute();
    delete(m_imageLQReqAction);
    m_imageLQReqAction = new ImageLQReqAction(m_transmissionQueue, 0, "");
    m_imageLQReqAction->execute();
    delete(m_imageLQReqAction);
    /* FIXME: se atora al agregar comandos a la cola */
//    m_imageLQReqAction = new ImageLQReqAction(m_transmissionQueue, 0, "/home/tesis/Repos/TESIS_V2/res/image.bmp");
//    m_imageLQReqAction->execute();
//    delete(m_imageLQReqAction);
}
