#include "EarthStation.h"
#include "ActionFactoryES.h"
#include "LedIASGetCommandReq.h"
#include "LedOBCGetCommandReq.h"
#include <QDebug>

#define ES_DB_CSV_FILE "dataBaseES.csv"

ImageManager *EarthStation::getImageManager() const
{
    return m_imageManager;
}

CommLinkMonitor *EarthStation::getCommLinkMonitor() const
{
    return m_commLinkMonitor;
}

ErrorManager *EarthStation::getErrorManager() const
{
    return m_errorManager;
}

bool EarthStation::getIASLedStatus() const
{
    return m_iasLedStatus;
}

void EarthStation::setIASLedStatus(bool iasLedStatus)
{
    //qDebug() << "setIASLedStatus(iasLedStatus = " << iasLedStatus << ")";
    if (iasLedStatus != m_iasLedStatus)
    {
        m_iasLedStatus = iasLedStatus;
        emit iasLedStatusChanged();
    }
}

bool EarthStation::getOBCLedStatus() const
{
    return m_obcLedStatus;
}

void EarthStation::setOBCLedStatus(bool obcLedStatus)
{
    //qDebug() << "setOBCLedStatus(obcLedStatus = " << obcLedStatus << ")";
    if (obcLedStatus != m_obcLedStatus)
    {
        m_obcLedStatus = obcLedStatus;
        emit obcLedStatusChanged();
    }
}

EarthStation::EarthStation(QString name, QString basePath, QObject *parent)
    : Computer(name, parent)
{
    m_errorManager = new ErrorManager();
    ImageDataBase *imageDataBase = new  ImageDataBase(basePath, ES_DB_CSV_FILE);
    TransmissionQueue *transmissionQueue = new TransmissionQueue();
    m_imageManager = new ImageManager(transmissionQueue, imageDataBase);
    m_commLinkMonitor = new CommLinkMonitor(transmissionQueue);
    ActionFactory *actionFactory = new ActionFactoryES(this, transmissionQueue, m_commLinkMonitor, imageDataBase, m_imageManager);
    ActionManager *actionManager = new ActionManager();
    CommManager *commManager = new CommManager(transmissionQueue, actionFactory, actionManager);
    commManager->addPort(PortId::ES_OBC_PORT, new SerialPortManager());
    commManager->addPort(PortId::ES_IAS_PORT, new SerialPortManager("EAV"));
    commManager->registerCommand(CommandCode::KEEPALIVE_REQ, PortId::ES_OBC_PORT);
    commManager->registerCommand(CommandCode::CAPTURE_REQ, PortId::ES_OBC_PORT);
    commManager->registerCommand(CommandCode::CATALOG_REQ, PortId::ES_OBC_PORT);
    commManager->registerCommand(CommandCode::IMAGE_HQ_REQ, PortId::ES_OBC_PORT);
    commManager->registerCommand(CommandCode::IMAGE_LQ_REQ, PortId::ES_OBC_PORT);
    commManager->registerCommand(CommandCode::DELETE_REQ, PortId::ES_OBC_PORT);
    commManager->registerCommand(CommandCode::CROP_REQ, PortId::ES_OBC_PORT);
    commManager->registerCommand(CommandCode::LED_IAS_GET_REQ, PortId::ES_OBC_PORT);
    commManager->registerCommand(CommandCode::LED_IAS_SET_REQ, PortId::ES_OBC_PORT);
    commManager->registerCommand(CommandCode::LED_OBC_GET_REQ, PortId::ES_OBC_PORT);
    commManager->registerCommand(CommandCode::LED_OBC_SET_REQ, PortId::ES_OBC_PORT);

    setActionManager(actionManager);
    setActionFactory(actionFactory);
    setCommManager(commManager);
    setTransmissionQueue(transmissionQueue);

    m_imageManager->getImageDataBase()->loadCSVFile();
    m_iasLedStatus = false;
    m_timer = new QTimer();
    connect(m_timer, &QTimer::timeout, this, [=]{
        //qDebug() << "connect Timeout LedIASGetCommandReq m_commLinkMonitor = " << m_commLinkMonitor << ", m_commLinkMonitor->isActive() = " << m_commLinkMonitor->isActive();
        if (m_commLinkMonitor && m_commLinkMonitor->isActive())
        {

        }

        //qDebug() << "Timeout Leds";
        static TransmissionQueue *aux = transmissionQueue;
        aux->addCommand(new LedOBCGetCommandReq());
        aux->addCommand(new LedIASGetCommandReq());
    });
    m_timer->start(5000);
}
