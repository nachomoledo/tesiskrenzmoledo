#include "ActionFactoryIAS.h"
#include "ImageAcquisitionSystem.h"
#include "gtest/gtest.h"


class ActionFactoryIASTest : public testing::Test
{
public:
    ActionFactoryIASTest()
    {
        m_actionFactoryIAS = new ActionFactoryIAS(m_ias);
    }

protected:
    //Class Under Test
    ActionFactory* m_actionFactoryIAS;
    // Dependencias
    ImageAcquisitionSystem *m_ias = nullptr;
};

TEST_F(ActionFactoryIASTest, functionTest)
{
    m_actionFactoryIAS->createAction(static_cast<int>(CommandCode::LED_IAS_GET_REQ), QByteArray());
    m_actionFactoryIAS->createAction(static_cast<int>(CommandCode::KEEPALIVE_REQ), QByteArray());
    m_actionFactoryIAS->createAction(static_cast<int>(CommandCode::CAPTURE_REQ), QByteArray());
    m_actionFactoryIAS->createAction(static_cast<int>(CommandCode::CROP_REQ), QByteArray());
    m_actionFactoryIAS->createAction(static_cast<int>(CommandCode::IMAGE_HQ_REQ), QByteArray());
    m_actionFactoryIAS->createAction(static_cast<int>(CommandCode::IMAGE_LQ_REQ), QByteArray());
    m_actionFactoryIAS->createAction(static_cast<int>(CommandCode::CATALOG_REQ), QByteArray());
    m_actionFactoryIAS->createAction(static_cast<int>(CommandCode::DELETE_REQ), QByteArray());
}
