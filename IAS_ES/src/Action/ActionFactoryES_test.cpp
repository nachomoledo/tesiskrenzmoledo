#include "ActionFactoryES.h"
#include "gtest/gtest.h"


class ActionFactoryESTest : public testing::Test
{
public:
    ActionFactoryESTest()
    {
        m_ActionFactoryES = new ActionFactoryES();
    }

protected:
    //Class Under Test
    ActionFactory* m_ActionFactoryES;
    // Dependencias

};

TEST_F(ActionFactoryESTest, functionTest)
{
    m_ActionFactoryES->createAction(static_cast<int>(CommandCode::KEEPALIVE_RES), QByteArray());
    m_ActionFactoryES->createAction(static_cast<int>(CommandCode::IMAGE_HQ_RES), QByteArray());
    m_ActionFactoryES->createAction(static_cast<int>(CommandCode::IMAGE_LQ_RES), QByteArray());
    m_ActionFactoryES->createAction(static_cast<int>(CommandCode::CATALOG_RES), QByteArray());
}
