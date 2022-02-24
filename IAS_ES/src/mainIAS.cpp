#include "ImagePropertiesViewModel.h"
#include "ViewModelManager.h"
#include "ImageFileInfo.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QStringList>
#include <QDebug>

#define BASE_PATH_IAS "/home/pi/Desktop/TESIS_V2/res/IAS"

void registerViewModelTypes(void);

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    ScreenProperties screenProperties;

    //TODO explicar que el usuario actúa siempre sobre la ET, y la acción puede quedarse en la ET o propagarse hasta la OBC o la IAS
    // EXPLICAR TAMBIÉN QUE NECESITO las referencias a la ias y la obc para setear los puertos, pero nada más
    ImageAcquisitionSystem *ias = new ImageAcquisitionSystem("Image Acquisition System", BASE_PATH_IAS);
    ias->setSerialPortName(PortId::IAS_OBC_PORT, "/dev/ttyS0");
    if (ias->isOpen(PortId::IAS_OBC_PORT))
    {
        ias->closePort(PortId::IAS_OBC_PORT);
    }
    ias->openPort(PortId::IAS_OBC_PORT);
    registerViewModelTypes();

    QObject::connect(&app, &QGuiApplication::aboutToQuit, ias, [=]{
        if (ias->isOpen(PortId::IAS_OBC_PORT))
        {
            ias->closePort(PortId::IAS_OBC_PORT);
        }
    });

    engine.load(QUrl(QStringLiteral("qrc:/mainIAS.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

void registerViewModelTypes(void)
{
    ViewModel::qmlRegisterViewModelType<ButtonViewModel>("ButtonViewModel");
    ViewModel::qmlRegisterViewModelType<TextFieldViewModel>("TextFieldViewModel");
    ViewModel::qmlRegisterViewModelType<InfoTextViewModel>("InfoTextViewModel");
    ViewModel::qmlRegisterViewModelType<AbstractScreenViewModel>("AbstractScreenViewModel");
    ViewModel::qmlRegisterViewModelType<ImagePropertiesViewModel>("ImagePropertiesViewModel");
    ViewModel::qmlRegisterViewModelType<MainScreenViewModel>("MainScreenViewModel");
    ScreenProperties::qmlRegisterType();
}
