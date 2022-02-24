#ifndef ABSTRACTTABVIEWMODEL_H
#define ABSTRACTTABVIEWMODEL_H

#include "ButtonViewModel.h"
#include "TextFieldViewModel.h"
#include "InfoTextViewModel.h"
#include <QList>

class AbstractScreenViewModel : public ViewModel
{
    Q_OBJECT
    Q_PROPERTY(QList<QObject*> textFieldList READ getTextFieldList CONSTANT)
    Q_PROPERTY(QList<QObject*> buttonList  READ getButtonList CONSTANT)
    Q_PROPERTY(QList<QObject*> infoTextList  READ getInfoTextList CONSTANT)

private:
    QList<QObject*> m_buttonList;
    QList<QObject*> m_textFieldList;
    QList<QObject*> m_infoTextList;

protected:
    void addButton(ButtonViewModel *buttonModel);
    void addTextField(TextFieldViewModel *textFieldModel);
    void addInfoText(InfoTextViewModel *infoTextModel);

public:
    AbstractScreenViewModel(QObject *parent = nullptr);
    QList<QObject *> getButtonList() const;
    QList<QObject *> getTextFieldList() const;
    QList<QObject *> getInfoTextList() const;
};

#endif // ABSTRACTTABVIEWMODEL_H
