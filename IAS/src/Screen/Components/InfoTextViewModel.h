#ifndef INFOTEXTVIEWMODEL_H
#define INFOTEXTVIEWMODEL_H

#include "ViewModel.h"

class InfoTextViewModel : public ViewModel
{
    Q_OBJECT
    Q_PROPERTY(QString title READ getTitle CONSTANT)
    Q_PROPERTY(QString value READ getValue NOTIFY valueChanged)

private:
    QString m_title;
    QString m_value;

public:
    InfoTextViewModel();
    InfoTextViewModel(QString title);
    QString getTitle() const;
    QString getValue() const;
    void setValue(const QString &value);

Q_SIGNALS:
    void valueChanged();
};

#endif // INFOTEXTVIEWMODEL_H
