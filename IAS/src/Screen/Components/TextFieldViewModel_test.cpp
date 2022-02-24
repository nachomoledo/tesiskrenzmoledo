#include "TextFieldViewModel.h"
#include "gtest/gtest.h"


class TextFieldViewModelTest : public testing::Test
{
public:
    TextFieldViewModelTest()
    {

    }

protected:
    //Class Under Test
    TextFieldViewModel* m_textFieldViewModel;
    // Dependencias

};

TEST_F(TextFieldViewModelTest, functionTest)
{
    TextFieldViewModel aux;
    aux.setText("name");
}
