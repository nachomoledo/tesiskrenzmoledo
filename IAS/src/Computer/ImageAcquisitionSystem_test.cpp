#include "ImageAcquisitionSystem.h"
#include "gtest/gtest.h"


class ImageAcquisitionSystemTest : public testing::Test
{
public:
    ImageAcquisitionSystemTest()
    {
        m_imageAcquisitionSystem = new ImageAcquisitionSystem("", "");
    }

protected:
    //Class Under Test
    ImageAcquisitionSystem* m_imageAcquisitionSystem;
    // Dependencias
};

TEST_F(ImageAcquisitionSystemTest, functionTest)
{

}
