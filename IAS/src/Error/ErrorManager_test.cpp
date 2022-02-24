#include "ErrorManager.h"
#include "gtest/gtest.h"


class ErrorManagerTest : public testing::Test
{
public:
    ErrorManagerTest()
    {
        m_errorManager = new ErrorManager();
    }

protected:
    //Class Under Test
    ErrorManager* m_errorManager;
    // Dependencias
};

TEST_F(ErrorManagerTest, functionTest)
{
    m_errorManager->setErrorMessage(ErrorId::NO_ERROR, "");
}
