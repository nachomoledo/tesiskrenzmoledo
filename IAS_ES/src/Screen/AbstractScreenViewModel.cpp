#include "AbstractScreenViewModel.h"
#include <QDebug>

QList<QObject *> AbstractScreenViewModel::getButtonList() const
{
    return m_buttonList;
}

QList<QObject *> AbstractScreenViewModel::getTextFieldList() const
{
    return m_textFieldList;
}

QList<QObject *> AbstractScreenViewModel::getInfoTextList() const
{
    return m_infoTextList;
}

void AbstractScreenViewModel::addButton(ButtonViewModel *buttonModel)
{
    if (buttonModel)
    {
        m_buttonList.append(buttonModel);
    }
}

void AbstractScreenViewModel::addTextField(TextFieldViewModel *textField)
{
    if (textField)
    {
        m_textFieldList.append(textField);
    }
}

void AbstractScreenViewModel::addInfoText(InfoTextViewModel *infoTextModel)
{
    if (infoTextModel)
    {
        m_infoTextList.append(infoTextModel);
    }
}

AbstractScreenViewModel::AbstractScreenViewModel(QObject *parent)
    : ViewModel(parent)
{

}
