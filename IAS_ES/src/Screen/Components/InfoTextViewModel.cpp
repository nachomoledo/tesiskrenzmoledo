#include "InfoTextViewModel.h"

QString InfoTextViewModel::getTitle() const
{
    return m_title;
}

QString InfoTextViewModel::getValue() const
{
    return m_value;
}

void InfoTextViewModel::setValue(const QString &value)
{
    if (value != m_value)
    {
        m_value = value;
        emit valueChanged();
    }
}

InfoTextViewModel::InfoTextViewModel()
    : ViewModel()
{

}

InfoTextViewModel::InfoTextViewModel(QString title)
    : ViewModel(), m_title(title)
{

}

