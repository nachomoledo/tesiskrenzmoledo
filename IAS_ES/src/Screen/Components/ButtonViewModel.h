#ifndef BUTTONVIEWMODEL_H
#define BUTTONVIEWMODEL_H

#include "ViewModel.h"

class ButtonViewModel : public ViewModel
{
    Q_OBJECT
    Q_PROPERTY(QString text READ getText NOTIFY textChanged)
    Q_PROPERTY(ButtonType type READ getType CONSTANT)
    Q_PROPERTY(bool enabled READ getEnabled NOTIFY enabledChanged)
    Q_PROPERTY(bool checked READ getChecked WRITE setChecked NOTIFY checkedChanged)

public:
    enum ButtonType
    {
        COMMON,
        CHECKEABLE,
        SWITCH
    };
    Q_ENUMS(ButtonType)

private:
    QString m_text;
    ButtonType m_type;
    bool m_enabled;
    bool m_checked;

public:
    ButtonViewModel();
    ButtonViewModel(QString text, ButtonType type, bool enabled = false);

    QString getText() const;
    void setText(const QString &text);
//    void setText(const QString &text);
    ButtonType getType() const;
//    void setType(const ButtonType &type);
    bool getEnabled() const;
    void setEnabled(bool enabled);

    bool getChecked() const;
    void setChecked(bool checked);

Q_SIGNALS:
    void clicked(void);
    void textChanged(void);
    void enabledChanged(void);
    void checkedChanged(void);
};

#endif // BUTTONVIEWMODEL_H
