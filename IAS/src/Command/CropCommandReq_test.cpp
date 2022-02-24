#include "CropCommandReq.h"
#include "gtest/gtest.h"


class CropCommandReqTest : public testing::Test
{
public:
    CropCommandReqTest()
    {
        m_cropCommandReq = new CropCommandReq(0, {ROI()});
    }

protected:
    //Class Under Test
    CropCommandReq* m_cropCommandReq;
    // Dependencias

};

TEST_F(CropCommandReqTest, functionTest)
{
    m_cropCommandReq->getRoiList();
    m_cropCommandReq->getCommandCode();
}
