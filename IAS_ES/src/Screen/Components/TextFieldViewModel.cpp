#include "TextFieldViewModel.h"
#include <QDebug>

QString TextFieldViewModel::getTitle() const
{
    return m_title;
}

QString TextFieldViewModel::getPlaceholderText() const
{
    return m_placeholderText;
}

void TextFieldViewModel::setText(const QString &text)
{
    //qDebug() << __FUNCTION__ << "m_text = " << m_text << ", text = " << text;

    if (m_text != text)
    {
        m_text = text;
        //qDebug() << __FUNCTION__ << "::textChanged(" << m_text << ")";
        emit textChanged(m_text);
    }
}

QString TextFieldViewModel::getText() const
{
    return m_text;
}

TextFieldViewModel::TextFieldViewModel()
    : ViewModel()
{

}

TextFieldViewModel::TextFieldViewModel(QString title, QString placeholderText)
    : ViewModel(), m_title(title), m_placeholderText(placeholderText)
{

}

