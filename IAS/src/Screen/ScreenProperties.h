#ifndef SCREENPROPERTIES_H
#define SCREENPROPERTIES_H

#include <QObject>
#include <QQmlEngine>

class ScreenProperties : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int width READ getScreenWidth CONSTANT)
    Q_PROPERTY(int height READ getScreenHeight CONSTANT)
    Q_PROPERTY(int buttonWidth READ getButtonWidth CONSTANT)
    Q_PROPERTY(int buttonHeight READ getButtonHeight CONSTANT)

public:
    ScreenProperties(QObject *parent = nullptr);
    int getScreenWidth(void);
    int getScreenHeight(void);
    int getButtonWidth(void);
    int getButtonHeight(void);
    static void qmlRegisterType() {
        qmlRegisterUncreatableType<ScreenProperties>("ViewModels", 1, 0, "ScreenProperties", "No se puede crear en QML. Las propiedades se definen en C++");
    }
};

#endif // SCREENPROPERTIES_H
