#include "ImagePropertiesViewModel.h"
#include "ViewModelManager.h"
#include "ImageFileInfo.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QStringList>
#include <QDebug>

#define BASE_PATH_ES "/home/tesis/Repos/TESIS_V2/res/ET"
#define BASE_PATH_IAS "/home/tesis/Repos/TESIS_V2/res/IAS"

void registerViewModelTypes(void);

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    ScreenProperties screenProperties;

    //TODO explicar que el usuario actúa siempre sobre la ET, y la acción puede quedarse en la ET o propagarse hasta la OBC o la IAS
    // EXPLICAR TAMBIÉN QUE NECESITO las referencias a la ias y la obc para setear los puertos, pero nada más
    EarthStation earthStation("Earth Station", BASE_PATH_ES);
    ImageAcquisitionSystem ias("Image Acquisition System", BASE_PATH_IAS);
    OnBoardComputer obc("On Board Computer");

    ViewModelManager viewModelManager(&earthStation, &ias, &obc);

    // Set Context Properties
    engine.rootContext()->setContextProperty("exposedViewModels", &viewModelManager);

    registerViewModelTypes();

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    QObject::connect(&app, &QGuiApplication::aboutToQuit, &viewModelManager, &ViewModelManager::closePorts);

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
