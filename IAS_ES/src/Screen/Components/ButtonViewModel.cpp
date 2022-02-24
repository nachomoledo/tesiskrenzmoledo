#include "ButtonViewModel.h"

QString ButtonViewModel::getText() const
{
    return m_text;
}

//void ButtonModel::setText(const QString &text)
//{
//    m_text = text;
//}

ButtonViewModel::ButtonType ButtonViewModel::getType() const
{
    return m_type;
}

//void ButtonModel::setType(const ButtonType &type)
//{
//    m_type = type;
//}

void ButtonViewModel::setText(const QString &text)
{
    if (m_text != text)
    {
        m_text = text;
        emit textChanged();
    }
}

bool ButtonViewModel::getEnabled() const
{
    return m_enabled;
}

void ButtonViewModel::setEnabled(bool enabled)
{
    if (m_enabled != enabled)
    {
        m_enabled = enabled;
        emit enabledChanged();
    }
}

bool ButtonViewModel::getChecked() const
{
    return m_checked;
}

void ButtonViewModel::setChecked(bool checked)
{
    if (m_checked != checked)
    {
        m_checked = checked;
        emit checkedChanged();
    }
}

ButtonViewModel::ButtonViewModel()
    : ViewModel()
{
    
}

ButtonViewModel::ButtonViewModel(QString text, ButtonType type, bool enabled)
    : ViewModel(), m_text(text), m_type(type), m_enabled(enabled), m_checked(false)
{

}

