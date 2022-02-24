#include "ActionFactoryOBC.h"
#include "gtest/gtest.h"


class ActionFactoryOBCTest : public testing::Test
{
public:
    ActionFactoryOBCTest()
    {
        m_actionFactoryOBC = new ActionFactoryOBC(nullptr);
    }

protected:
    //Class Under Test
    ActionFactory* m_actionFactoryOBC;
    // Dependencias

};

TEST_F(ActionFactoryOBCTest, functionTest)
{
    m_actionFactoryOBC->createAction(static_cast<int>(CommandCode::LED_OBC_GET_REQ), QByteArray());
    m_actionFactoryOBC->createAction(static_cast<int>(CommandCode::LED_OBC_SET_REQ), QByteArray());
}
