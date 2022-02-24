#include "ImageManager.h"
#include "gtest/gtest.h"


class ImageManagerTest : public testing::Test
{
public:
    ImageManagerTest()
    {
        m_transmissionQueue = new TransmissionQueue();
        m_imageManager = new ImageManager(m_transmissionQueue, nullptr, nullptr, nullptr);
    }

protected:
    //Class Under Test
    ImageManager* m_imageManager;
    // Dependencias
    TransmissionQueue *m_transmissionQueue;
    ImageDataBase *m_imageDataBase = new ImageDataBase("", "");
    ImageEditor *m_imageEditor = new ImageEditor();
};

TEST_F(ImageManagerTest, functionTest)
{
    m_imageManager->sendImageCommandReqMessage(0, 0);
    m_imageManager->sendCatalogCommandReqMessage();
    m_imageManager->sendDeleteReqMessage(0);
    m_imageManager->selectROI(0);
    m_imageManager->getImageDataBase();
    m_imageManager->sendCaptureReqMessage(false);
    m_imageManager->getImageEditor();
    delete(m_imageManager);
    m_imageManager = new ImageManager(m_transmissionQueue, m_imageDataBase, m_imageEditor);
}
