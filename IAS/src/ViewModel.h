#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include <QObject>
#include <QQmlEngine>
#include <typeinfo>

class ViewModel : public QObject
{
    Q_OBJECT
public:
    ViewModel(QObject *parent = nullptr);
    template <class T>
    static void qmlRegisterViewModelType(const char *typeName) {
        qmlRegisterUncreatableType<T>("ViewModels", 1, 0, typeName, "Es un viewModel, no se puede crear en QML");
    }
};

#endif // VIEWMODEL_H
