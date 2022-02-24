#include "Operators.h"
#include "gtest/gtest.h"

class OperatorsTest : public testing::Test
{
public:
    OperatorsTest()
    {

    }

protected:
    //Class Under Test
    // Dependencias
};

TEST_F(OperatorsTest, QByteArray16)
{
    QByteArray expected("AB");
    QByteArray test;
    test << quint8(65) << quint8(66);
    ASSERT_EQ(expected, test);
}


