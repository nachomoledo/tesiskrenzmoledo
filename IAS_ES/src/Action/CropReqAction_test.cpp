#include "CropReqAction.h"
#include "gtest/gtest.h"


class CropReqActionTest : public testing::Test
{
public:
    CropReqActionTest()
    {
        transmissionQueue = new TransmissionQueue();
        imageManagerIAS = new ImageManagerIAS(transmissionQueue);
        m_cropReqAction = new CropReqAction(imageManagerIAS, imageId, roiList);
    }

protected:
    //Class Under Test
    CropReqAction* m_cropReqAction;
    // Dependencias
    TransmissionQueue *transmissionQueue;
    ImageManagerIAS *imageManagerIAS;
    quint16 imageId = 0;
    QList<ROI> roiList;
};

TEST_F(CropReqActionTest, functionTest)
{
    m_cropReqAction->execute();
    m_cropReqAction = new CropReqAction(nullptr, imageId, roiList);
    m_cropReqAction->execute();
}
