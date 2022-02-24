#include "OnBoardComputer.h"
#include "gtest/gtest.h"


class OnBoardComputerTest : public testing::Test
{
public:
    OnBoardComputerTest()
    {
        m_onBoardComputer = new OnBoardComputer("");
    }

protected:
    //Class Under Test
    OnBoardComputer* m_onBoardComputer;
    // Dependencias

};

TEST_F(OnBoardComputerTest, functionTest)
{

}
