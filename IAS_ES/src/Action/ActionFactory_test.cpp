#include "ActionFactory.h"
#include "gtest/gtest.h"

class ActionFactoryChild : public ActionFactory
{
public:
    ActionFactoryChild()
        : ActionFactory()
    {
        registerCreateActionFn(0, &ActionFactoryChild::createAction);
    };
    static Action* createAction(const QByteArray &packet)
    {
        return nullptr;
    };
};

class ActionFactoryTest : public testing::Test
{
public:
    ActionFactoryTest()
    {
        m_actionFactory = new ActionFactory();
    }

protected:
    //Class Under Test
    ActionFactory* m_actionFactory;
    // Dependencias

};

TEST_F(ActionFactoryTest, functionTest)
{
    ActionFactory *aux = new ActionFactoryChild();
    m_actionFactory->createAction(0, QByteArray());
    aux->createAction(0, QByteArray());
}
