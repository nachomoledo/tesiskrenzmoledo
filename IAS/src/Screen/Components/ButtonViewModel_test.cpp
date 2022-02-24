#include "ButtonViewModel.h"
#include "gtest/gtest.h"


class ButtonViewModelTest : public testing::Test
{
public:
    ButtonViewModelTest()
    {
        m_ButtonViewModel = new ButtonViewModel("", ButtonViewModel::ButtonType::COMMON);
    }

protected:
    //Class Under Test
    ButtonViewModel* m_ButtonViewModel;

    // Dependencias

};

TEST_F(ButtonViewModelTest, functionTest)
{
    ButtonViewModel aux;
    m_ButtonViewModel->getText();
    m_ButtonViewModel->setText("name");
    m_ButtonViewModel->getType();
    m_ButtonViewModel->getEnabled();
    m_ButtonViewModel->setEnabled(false);
    m_ButtonViewModel->setEnabled(true);
    m_ButtonViewModel->getChecked();
    m_ButtonViewModel->setChecked(false);
    m_ButtonViewModel->setChecked(true);
}
