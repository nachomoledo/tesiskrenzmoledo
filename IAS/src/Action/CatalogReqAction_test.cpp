#include "CatalogReqAction.h"
#include "gtest/gtest.h"


class CatalogReqActionTest : public testing::Test
{
public:
    CatalogReqActionTest()
    {
        m_transmissionQueue = new TransmissionQueue();
        m_imageDataBase = new ImageDataBase("","");
        m_catalogReqAction = new CatalogReqAction(nullptr, nullptr);
    }

protected:
    //Class Under Test
    CatalogReqAction* m_catalogReqAction;
    // Dependencias
    TransmissionQueue *m_transmissionQueue;
    ImageDataBase *m_imageDataBase;
};

TEST_F(CatalogReqActionTest, functionTest)
{
    m_catalogReqAction->execute();
    delete(m_catalogReqAction);
    m_catalogReqAction = new CatalogReqAction(m_transmissionQueue, m_imageDataBase);
    m_catalogReqAction->execute();

}
