#ifndef TEXTFIELDVIEWMODEL_H
#define TEXTFIELDVIEWMODEL_H

#include "ViewModel.h"

class TextFieldViewModel : public ViewModel
{
    Q_OBJECT
    Q_PROPERTY(QString title READ getTitle CONSTANT)
    Q_PROPERTY(QString placeholderText READ getPlaceholderText CONSTANT)

private:
    QString m_title;
    QString m_placeholderText;
    QString m_text;

public:
    TextFieldViewModel();
    TextFieldViewModel(QString title, QString placeholderText);
    QString getTitle() const;
    QString getPlaceholderText() const;
    Q_INVOKABLE void setText(const QString &text);

    QString getText() const;

Q_SIGNALS:
    void textChanged(QString text);
};

#endif // TEXTFIELDVIEWMODEL_H
