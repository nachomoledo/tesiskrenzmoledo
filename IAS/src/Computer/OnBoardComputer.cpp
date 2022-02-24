#include "OnBoardComputer.h"
#include "ActionFactoryOBC.h"

#define ES_PORT 1
#define IAS_PORT 2

OnBoardComputer::OnBoardComputer(QString name)
    : Computer(name)
{
    m_led = false;
    TransmissionQueue *transmissionQueue = new TransmissionQueue();
    ActionManager *actionManager = new ActionManager();
    ActionFactory *actionFactory = new ActionFactoryOBC(this, transmissionQueue);
    CommManager *commManager = new CommManager(transmissionQueue, actionFactory, actionManager);
    commManager->addPort(PortId::OBC_ES_PORT, new SerialPortManager());
    commManager->addPort(PortId::OBC_IAS_PORT, new SerialPortManager());
    commManager->registerCommand(CommandCode::LED_OBC_GET_REQ, PortId::OBC_ES_PORT);
    commManager->registerCommand(CommandCode::LED_OBC_GET_RES, PortId::OBC_ES_PORT);
    commManager->registerCommand(CommandCode::LED_OBC_SET_REQ, PortId::OBC_ES_PORT);
    commManager->registerForwardingCommand(CommandCode::KEEPALIVE_REQ, PortId::OBC_IAS_PORT);
    commManager->registerForwardingCommand(CommandCode::KEEPALIVE_RES, PortId::OBC_ES_PORT);
    commManager->registerForwardingCommand(CommandCode::CAPTURE_REQ, PortId::OBC_IAS_PORT);
    commManager->registerForwardingCommand(CommandCode::CATALOG_REQ, PortId::OBC_IAS_PORT);
    commManager->registerForwardingCommand(CommandCode::CATALOG_RES, PortId::OBC_ES_PORT);
    commManager->registerForwardingCommand(CommandCode::IMAGE_HQ_REQ, PortId::OBC_IAS_PORT);
    commManager->registerForwardingCommand(CommandCode::IMAGE_LQ_REQ, PortId::OBC_IAS_PORT);
    commManager->registerForwardingCommand(CommandCode::IMAGE_LQ_RES, PortId::OBC_ES_PORT);
    commManager->registerForwardingCommand(CommandCode::DELETE_REQ, PortId::OBC_IAS_PORT);
    commManager->registerForwardingCommand(CommandCode::CROP_REQ, PortId::OBC_IAS_PORT);
    commManager->registerForwardingCommand(CommandCode::LED_IAS_GET_REQ, PortId::OBC_IAS_PORT);
    commManager->registerForwardingCommand(CommandCode::LED_IAS_GET_RES, PortId::OBC_ES_PORT);
    commManager->registerForwardingCommand(CommandCode::LED_IAS_SET_REQ, PortId::OBC_IAS_PORT);
    setCommManager(commManager);
    setActionManager(actionManager);
    setActionFactory(actionFactory);
}

bool OnBoardComputer::getLed() const
{
    return m_led;
}

void OnBoardComputer::setLed(bool led)
{
    m_led = led;
}
