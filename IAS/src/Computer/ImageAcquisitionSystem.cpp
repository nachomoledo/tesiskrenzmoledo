#include "ImageAcquisitionSystem.h"
#include "ActionFactoryIAS.h"
#include "ImageManagerIAS.h"

#define IAS_DB_CSV_FILE "dataBaseIAS.csv"

bool ImageAcquisitionSystem::getLed() const
{
    return m_led;
}

void ImageAcquisitionSystem::setLed(bool led)
{
    m_led = led;
}

ImageAcquisitionSystem::ImageAcquisitionSystem(QString name, QString basePath)
    : Computer(name)
{
    m_led = false;
    TransmissionQueue *transmissionQueue = new TransmissionQueue();
    ImageDataBase *imageDataBase = new  ImageDataBase(basePath, IAS_DB_CSV_FILE);
    ImageEditor *imageEditor = new ImageEditor();
    CameraManager *cameraManager = new CameraManager(basePath);
    m_imageManager = new ImageManagerIAS(transmissionQueue, imageDataBase, imageEditor, cameraManager);
    ActionManager *actionManager = new ActionManager();
    ActionFactory *actionFactory = new ActionFactoryIAS(this, transmissionQueue, imageDataBase, static_cast<ImageManagerIAS*>(m_imageManager));
    CommManager *commManager = new CommManager(transmissionQueue, actionFactory, actionManager);
    commManager->addPort(PortId::IAS_OBC_PORT, new SerialPortManager());
    commManager->addPort(PortId::IAS_ES_PORT, new SerialPortManager());
    commManager->registerCommand(CommandCode::KEEPALIVE_RES, PortId::IAS_OBC_PORT);
    commManager->registerCommand(CommandCode::CATALOG_RES, PortId::IAS_OBC_PORT);
    commManager->registerCommand(CommandCode::IMAGE_LQ_RES, PortId::IAS_OBC_PORT);
    commManager->registerCommand(CommandCode::IMAGE_HQ_RES, PortId::IAS_ES_PORT);
    commManager->registerCommand(CommandCode::LED_IAS_GET_RES, PortId::IAS_OBC_PORT);
    setCommManager(commManager);
    setActionManager(actionManager);
    setActionFactory(actionFactory);
    m_imageManager->getImageDataBase()->buildCatalog();
    m_imageManager->getImageDataBase()->loadCSVFile();
}
