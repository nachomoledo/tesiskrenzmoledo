#include "CatalogResAction.h"
#include "gtest/gtest.h"


class CatalogResActionTest : public testing::Test
{
public:
    CatalogResActionTest()
    {
        dataBase = new ImageDataBase("","");
        imageProperties = new ImageProperties(0, "", "", "", 0);
        m_catalogResAction = new CatalogResAction(nullptr, 0, nullptr, 0, 0);
    }

protected:
    //Class Under Test
    CatalogResAction* m_catalogResAction;
    // Dependencias
    ImageDataBase *dataBase;
    ImageProperties *imageProperties;
};

TEST_F(CatalogResActionTest, functionTest)
{
    m_catalogResAction->execute();
    delete(m_catalogResAction);
    m_catalogResAction = new CatalogResAction(dataBase, 0, imageProperties, 0, 0);
    m_catalogResAction->execute();
}
