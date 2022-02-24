#include "CameraManager.h"
#include "gtest/gtest.h"


class CameraManagerTest : public testing::Test
{
public:
    CameraManagerTest()
    {
        m_cameraManager = new CameraManager("");
    }

protected:
    //Class Under Test
    CameraManager* m_cameraManager;
    // Dependencias

};

TEST_F(CameraManagerTest, functionTest)
{
    m_cameraManager->captureImageWebcam(0);
    m_cameraManager->captureImageIPCam(0);
}
