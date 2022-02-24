#include "ViewModelManager.h"
#include "ImagePropertiesViewModel.h"
#include "Defines.h"
#include "LedIASSetCommandReq.h"
#include "LedOBCSetCommandReq.h"
#include <QtConcurrent>

MainScreenViewModel *ViewModelManager::getMainScreenViewModel() const
{
    return m_mainScreenViewModel;
}

ScreenProperties *ViewModelManager::getScreenProperties() const
{
    return m_screenProperties;
}

ViewModelManager::ViewModelManager(EarthStation *earthStation, ImageAcquisitionSystem *ias, OnBoardComputer *obc)
    : m_earthStation(earthStation), m_ias(ias), m_obc(obc)
{
    m_mainScreenViewModel = new MainScreenViewModel(earthStation->getImageManager());
    m_screenProperties = new ScreenProperties();

    if (m_mainScreenViewModel)
    {
        TextFieldViewModel *ESOBCPort = m_mainScreenViewModel->getESOBCPort();
        if (ESOBCPort)
        {
            connect(ESOBCPort, &TextFieldViewModel::textChanged, this, &ViewModelManager::onESOBCPortChanged);
            if (ESOBCPort->getText() != "")
            {
                onESOBCPortChanged(ESOBCPort->getText());
            }
        }
        TextFieldViewModel *ESIASPort = m_mainScreenViewModel->getESIASPort();
        if (ESIASPort)
        {
            connect(ESIASPort, &TextFieldViewModel::textChanged, this, &ViewModelManager::onESIASPortChanged);
            if (ESIASPort->getText() != "")
            {
                onESIASPortChanged(ESIASPort->getText());
            }
        }
        TextFieldViewModel *OBCESPort = m_mainScreenViewModel->getOBCESPort();
        if (OBCESPort)
        {
            connect(OBCESPort, &TextFieldViewModel::textChanged, this, &ViewModelManager::onOBCESPortChanged);
            if (OBCESPort->getText() != "")
            {
                onOBCESPortChanged(OBCESPort->getText());
            }
        }
        TextFieldViewModel *OBCIASPort = m_mainScreenViewModel->getOBCIASPort();
        if (OBCIASPort)
        {
            connect(OBCIASPort, &TextFieldViewModel::textChanged, this, &ViewModelManager::onOBCIASPortChanged);
            if (OBCIASPort->getText() != "")
            {
                onOBCIASPortChanged(OBCIASPort->getText());
            }
        }
        TextFieldViewModel *IASOBCPort = m_mainScreenViewModel->getIASOBCPort();
        if (IASOBCPort)
        {
            connect(IASOBCPort, &TextFieldViewModel::textChanged, this, &ViewModelManager::onIASOBCPortChanged);
            if (IASOBCPort->getText() != "")
            {
                onIASOBCPortChanged(IASOBCPort->getText());
            }
        }
        TextFieldViewModel *IASESPort = m_mainScreenViewModel->getIASESPort();
        if (IASESPort)
        {
            connect(IASESPort, &TextFieldViewModel::textChanged, this, &ViewModelManager::onIASESPortChanged);
            if (IASESPort->getText() != "")
            {
                onIASESPortChanged(IASESPort->getText());
            }
        }

        ButtonViewModel *connectButton = m_mainScreenViewModel->getConnectButton();
        if (connectButton)
        {
//            connectButton->setEnabled(true);
            connect(connectButton, &ButtonViewModel::clicked, this, &ViewModelManager::onConnectedClicked);
        }

        ButtonViewModel *captureButton = m_mainScreenViewModel->getCaptureButton();
        if (captureButton)
        {
//            captureButton->setEnabled(true);
            connect(captureButton, &ButtonViewModel::clicked, this, &ViewModelManager::onCaptureClicked);
        }

        ButtonViewModel *updateCatalogButton = m_mainScreenViewModel->getUpdateCatalogButton();
        if (updateCatalogButton)
        {
//            updateCatalogButton->setEnabled(true);
            connect(updateCatalogButton, &ButtonViewModel::clicked, this, &ViewModelManager::onUpdateCatalogClicked);
        }

        ButtonViewModel *autoUpdateButton = m_mainScreenViewModel->getSyncCatalogButton();
        if (autoUpdateButton)
        {
//            autoUpdateButton->setEnabled(true);
            connect(autoUpdateButton, &ButtonViewModel::clicked, this, &ViewModelManager::onAutoUpdateClicked);
        }

        ButtonViewModel *downloadHQButton = m_mainScreenViewModel->getDownloadInHQButton();
        if (downloadHQButton)
        {
//            downloadHQButton->setEnabled(true);
            connect(downloadHQButton, &ButtonViewModel::clicked, this, &ViewModelManager::onDownloadHQClicked);
        }

        ButtonViewModel *downloadLQButton = m_mainScreenViewModel->getDownloadSamplesButton();
        if (downloadLQButton)
        {
//            downloadLQButton->setEnabled(true);
            connect(downloadLQButton, &ButtonViewModel::clicked, this, &ViewModelManager::onDownloadLQClicked);
        }

        ButtonViewModel *deleteButton = m_mainScreenViewModel->getDeleteButton();
        if (deleteButton)
        {
//            deleteButton->setEnabled(true);
            connect(deleteButton, &ButtonViewModel::clicked, this, &ViewModelManager::onDeleteClicked);
        }

        ButtonViewModel *cropButton = m_mainScreenViewModel->getCropButton();
        if (cropButton)
        {
//            cropButton->setEnabled(true);
            connect(cropButton, &ButtonViewModel::clicked, this, &ViewModelManager::onCropClicked);
        }

        ButtonViewModel *toggleLedOBCButton = m_mainScreenViewModel->getSetLedOBCButton();
        if (toggleLedOBCButton)
        {
            connect(toggleLedOBCButton, &ButtonViewModel::clicked, this, [&]{
                if (m_earthStation)
                {
                    bool currentStatus = m_earthStation->getOBCLedStatus();
                    TransmissionQueue *transmissionQueue = m_earthStation->getTransmissionQueue();
                    if (transmissionQueue)
                    {
                        transmissionQueue->addCommand(new LedOBCSetCommandReq(!currentStatus));
                    }
                }
            });
        }

        ButtonViewModel *toggleLedIASButton = m_mainScreenViewModel->getSetLedIASButton();
        if (toggleLedIASButton)
        {
//            cropButton->setEnabled(true);
            connect(toggleLedIASButton, &ButtonViewModel::clicked, this, [&]{
                //guardar estado anterior
                if (m_earthStation)
                {
                    bool currentStatus = m_earthStation->getIASLedStatus();
                    TransmissionQueue *transmissionQueue = m_earthStation->getTransmissionQueue();
                    if (transmissionQueue)
                    {
                        transmissionQueue->addCommand(new LedIASSetCommandReq(!currentStatus));
                    }
                }
            });
        }

        ButtonViewModel *openHQImagesButton = m_mainScreenViewModel->getOpenHQImagesButton();
        if (openHQImagesButton)
        {
//            downloadHQButton->setEnabled(true);
            connect(openHQImagesButton, &ButtonViewModel::clicked, this, []{
                QString command = "/home/tesis/Repos/TESIS_V2/res/openHQ.sh";
                //QtConcurrent::run(QThreadPool::globalInstance(), system, command.toLocal8Bit().data());
                system(command.toLocal8Bit().data());
                //qDebug() << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<< ABRO HQ";
                });
        }

        ButtonViewModel *catalogButton = m_mainScreenViewModel->getOpenCatalogButton();
        if (catalogButton)
        {
//            downloadHQButton->setEnabled(true);
            connect(catalogButton, &ButtonViewModel::clicked, this, []{
                QString command = "/home/tesis/Repos/TESIS_V2/res/openLQ.sh";
                //QtConcurrent::run(QThreadPool::globalInstance(), system, command.toLocal8Bit().data());
                system(command.toLocal8Bit().data());
                //qDebug() << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<< ABRO LQ";
                });
        }

        ButtonViewModel *camSelectButton = m_mainScreenViewModel->getCamSelectButton();
        if (camSelectButton)
        {
            camSelectButton->setChecked(true);
        }
    }

    if (m_earthStation)
    {
        ErrorManager *errorManager = m_earthStation->getErrorManager();
        if (errorManager)
        {
            connect(errorManager, &ErrorManager::errorMessageChanged, this, &ViewModelManager::onErrorChanged);
        }

        CommLinkMonitor *commLinkMonitor = m_earthStation->getCommLinkMonitor();
        if(commLinkMonitor)
        {
            onCommStatusChanged(commLinkMonitor->getCommStatus());
            connect(commLinkMonitor, &CommLinkMonitor::commStatusChanged, this, &ViewModelManager::onCommStatusChanged);
            connect(commLinkMonitor, &CommLinkMonitor::autoUpdateChanged, this, &ViewModelManager::onAutoUpdateChanged);
        }

        CommManager *commManagerES = m_earthStation->getCommManager();
        if (commManagerES)
        {
            connect(commManagerES, &CommManager::portOpened, this, &ViewModelManager::onPortOpened);
            connect(commManagerES, &CommManager::lostMessagesChanged, this, &ViewModelManager::onLostMessagesChanged);
            connect(commManagerES, &CommManager::sentMessagesChanged, this, &ViewModelManager::onSentMessagesChanged);
            connect(commManagerES, &CommManager::receivedMessagesChanged, this, &ViewModelManager::onReceivedMessagesChanged);

            connect(commManagerES, &CommManager::sentLedOBCReqMessagesChanged, this, [=](quint32 total){
                if (m_mainScreenViewModel)
                {
                    InfoTextViewModel *sentLedOBCReqMessagesText = m_mainScreenViewModel->getSentLedOBCReqMessages();

                    if (sentLedOBCReqMessagesText)
                    {
                        sentLedOBCReqMessagesText->setValue(QString::number(total));
                    }
                }
            });
            connect(commManagerES, &CommManager::receivedLedOBCResMessagesChanged, this, [=](quint32 total){
                if (m_mainScreenViewModel)
                {
                    InfoTextViewModel *receivedLedOBCResMessagesText = m_mainScreenViewModel->getReceivedLedOBCResMessages();

                    if (receivedLedOBCResMessagesText)
                    {
                        receivedLedOBCResMessagesText->setValue(QString::number(total));
                    }
                }
            });
            connect(commManagerES, &CommManager::sentLedIASReqMessagesChanged, this, [=](quint32 total){
                if (m_mainScreenViewModel)
                {
                    InfoTextViewModel *sentLedIASReqMessagesText = m_mainScreenViewModel->getSentLedIASReqMessages();

                    if (sentLedIASReqMessagesText)
                    {
                        sentLedIASReqMessagesText->setValue(QString::number(total));
                    }
                }
            });
            connect(commManagerES, &CommManager::receivedLedIASResMessagesChanged, this, [=](quint32 total){
                if (m_mainScreenViewModel)
                {
                    InfoTextViewModel *receivedLedIASResMessagesText = m_mainScreenViewModel->getReceivedLedIASResMessages();

                    if (receivedLedIASResMessagesText)
                    {
                        receivedLedIASResMessagesText->setValue(QString::number(total));
                    }
                }
            });
        }

        ImageManager *imageManager = m_earthStation->getImageManager();
        if (imageManager)
        {
            ImageDataBase *imageDataBase = imageManager->getImageDataBase();
            if (imageDataBase)
            {
                buildCatalog(imageDataBase->getImageMap());
                connect(imageDataBase, &ImageDataBase::imageMapChanged, this, [=]{this->buildCatalog(imageDataBase->getImageMap());});
            }
        }

        connect(m_earthStation, &EarthStation::obcLedStatusChanged, this, [=]{emit this->obcLedStatusChanged();});
        connect(m_earthStation, &EarthStation::iasLedStatusChanged, this, [=]{emit this->iasLedStatusChanged();});
    }

    if (m_obc)
    {
        CommManager *commManagerOBC = m_obc->getCommManager();
        if (commManagerOBC)
        {
            connect(commManagerOBC, &CommManager::portOpened, this, &ViewModelManager::onPortOpened);
        }
    }
}

void ViewModelManager::buildCatalog(QMap<unsigned short, ImageProperties *> map)
{
    //qDebug() << "ViewModelManager::buildCatalog map->size = " << map.size();
    QList<QObject *> list;
//    QList<unsigned short> keys = map.keys();
    QList<ImageProperties *> values = map.values();
    for (int i = 0; i < map.size(); i++)
    {
        ImageProperties *value = values[i];
        if (value)
        {
            list.append(new ImagePropertiesViewModel(*value));
        }
    }

    if (m_mainScreenViewModel)
    {
        m_mainScreenViewModel->setCatalog(list);
    }

    m_selectedImages.clear();
}

void ViewModelManager::onLostMessagesChanged(quint32 total)
{
    if (m_mainScreenViewModel)
    {
        InfoTextViewModel *lostMessagesText = m_mainScreenViewModel->getLostMessages();

        if (lostMessagesText)
        {
            lostMessagesText->setValue(QString::number(total));
        }
    }
}

void ViewModelManager::onSentMessagesChanged(quint32 total)
{
    if (m_mainScreenViewModel)
    {
        InfoTextViewModel *sentMessagesText = m_mainScreenViewModel->getSentMesseges();

        if (sentMessagesText)
        {
            sentMessagesText->setValue(QString::number(total));
        }
    }
}

void ViewModelManager::onReceivedMessagesChanged(quint32 total)
{
    if (m_mainScreenViewModel)
    {
        InfoTextViewModel *receivedMessagesText = m_mainScreenViewModel->getReceivedMesseges();

        if (receivedMessagesText)
        {
            receivedMessagesText->setValue(QString::number(total));
        }
    }
}

void ViewModelManager::onPortOpened(PortId portId)
{
    Q_UNUSED(portId)
    //qDebug() << "ViewModelManager::onPortOpened";
    CommLinkMonitor *commLinkMonitor = m_earthStation->getCommLinkMonitor();
    ButtonViewModel *connectButton = m_mainScreenViewModel->getConnectButton();
    ButtonViewModel *downloadHQButton = m_mainScreenViewModel->getDownloadInHQButton();
    ButtonViewModel *toggleLedOBCButton = m_mainScreenViewModel->getSetLedOBCButton();
    ButtonViewModel *toggleLedIASButton = m_mainScreenViewModel->getSetLedIASButton();

    if (m_earthStation)
    {
        if (portId == PortId::ES_OBC_PORT)
        {
            if (m_earthStation->isOpen(PortId::ES_OBC_PORT) && commLinkMonitor)
            {
                onCommStatusChanged(commLinkMonitor->getCommStatus());
                connectButton->setEnabled(true);
                toggleLedOBCButton->setEnabled(true);
                toggleLedIASButton->setEnabled(true);
                downloadHQButton->setEnabled(true);      //fixme
            }
            else
            {
                connectButton->setEnabled(false);
                toggleLedOBCButton->setEnabled(false);
                toggleLedIASButton->setEnabled(false);
                downloadHQButton->setEnabled(false);    //fixme
            }
        }
//        else if (portId == PortId::ES_IAS_PORT)
//        {
//            if ((m_earthStation->isOpen(PortId::ES_IAS_PORT)) && (commLinkMonitor->getCommStatus() == CommStatus::CONNECTED))
//            {
//                downloadHQButton->setEnabled(true);
//            }
//            else
//            {
//                downloadHQButton->setEnabled(false);
//            }
//        }
    }
}

QString ViewModelManager::getImageToShow() const
{
    //return "file:/home/tesis/Repos/TESIS_V2/res/ET/3.jpg";
    return m_imageToShow;
}

ButtonViewModel* ViewModelManager::getSetLedOBCButton()
{
    if (m_mainScreenViewModel)
    {
        return m_mainScreenViewModel->getSetLedOBCButton();
    }
    return nullptr;
}

ButtonViewModel* ViewModelManager::getSetLedIASButton()
{
    if (m_mainScreenViewModel)
    {
        return m_mainScreenViewModel->getSetLedIASButton();
    }
    return nullptr;
}

void ViewModelManager::onImageAdded(int id)
{
    //qDebug() << "ViewModelManager::onImageAdded(id = " << id << ")";
    ImageDataBase *imageDataBase;
    QString imageToShow = "";
    if (m_earthStation && m_earthStation->getImageManager())
    {
        //qDebug() << "if 1";
        imageDataBase = m_earthStation->getImageManager()->getImageDataBase();
        if (imageDataBase)
        {
            //qDebug() << "if 2";
            if (imageDataBase->isDownloaded(id, LOW_QUALITY_EXTENSION))
            {
                //qDebug() << "if 3";
                imageToShow = imageDataBase->getImageBasePathAndNameWithExtension(id, LOW_QUALITY_EXTENSION);
            }
        }
    }
    setImageToShow(imageToShow);
}

void ViewModelManager::setImageToShow(const QString &imageToShow)
{
    //qDebug() << "ViewModelManager::setImageToShow imageToShow = " << imageToShow;
    if (imageToShow != m_imageToShow)
    {
        m_imageToShow = (imageToShow != "") ? ("file:" + imageToShow) : "";
        emit imageToShowChanged();
    }
}

void ViewModelManager::onESOBCPortChanged(QString text)
{
    //qDebug() << "onESOBCPortChanged!!! -> " << text;
    if (m_earthStation)
    {
        if(m_earthStation->isOpen(PortId::ES_OBC_PORT))
        {
            m_earthStation->closePort(PortId::ES_OBC_PORT);
        }
        m_earthStation->setSerialPortName(PortId::ES_OBC_PORT, text);
        m_earthStation->openPort(PortId::ES_OBC_PORT);
    }
}

void ViewModelManager::onESIASPortChanged(QString text)
{
    //qDebug() << "onESIASPortChanged!!!" << text;
    if (m_earthStation)
    {
        if(m_earthStation->isOpen(PortId::ES_IAS_PORT))
        {
            m_earthStation->closePort(PortId::ES_IAS_PORT);
        }
        m_earthStation->setSerialPortName(PortId::ES_IAS_PORT, text);
        m_earthStation->openPort(PortId::ES_IAS_PORT);
    }
}

void ViewModelManager::onOBCESPortChanged(QString text)
{
    //qDebug() << "onOBCESPortChanged!!!" << text;
    if (m_obc)
    {
        if(m_obc->isOpen(PortId::OBC_ES_PORT))
        {
            m_obc->closePort(PortId::OBC_ES_PORT);
        }
        m_obc->setSerialPortName(PortId::OBC_ES_PORT, text);
        m_obc->openPort(PortId::OBC_ES_PORT);
    }
}

void ViewModelManager::onOBCIASPortChanged(QString text)
{
    //qDebug() << "onOBCIASPortChanged!!! -> " << text;
    if (m_obc)
    {
        if(m_obc->isOpen(PortId::OBC_IAS_PORT))
        {
            m_obc->closePort(PortId::OBC_IAS_PORT);
        }
        m_obc->setSerialPortName(PortId::OBC_IAS_PORT, text);
        m_obc->openPort(PortId::OBC_IAS_PORT);
    }
}

void ViewModelManager::onIASOBCPortChanged(QString text)
{
    //qDebug() << "onIASOBCPortChanged!!!" << text;
    if (m_ias)
    {
        if(m_ias->isOpen(PortId::IAS_OBC_PORT))
        {
            m_ias->closePort(PortId::IAS_OBC_PORT);
        }
        m_ias->setSerialPortName(PortId::IAS_OBC_PORT, text);
        m_ias->openPort(PortId::IAS_OBC_PORT);
    }
}

void ViewModelManager::onIASESPortChanged(QString text)
{
    //qDebug() << "onIASESPortChanged!!!" << text;
    if (m_ias)
    {
        if(m_ias->isOpen(PortId::IAS_ES_PORT))
        {
            m_ias->closePort(PortId::IAS_ES_PORT);
        }
        m_ias->setSerialPortName(PortId::IAS_ES_PORT, text);
        m_ias->openPort(PortId::IAS_ES_PORT);
    }
}

void ViewModelManager::onConnectedClicked()
{
    //qDebug() << "onConnectedClicked!!!";
    CommLinkMonitor *commLinkMonitor = m_earthStation->getCommLinkMonitor();
    if (commLinkMonitor)
    {
        if (!commLinkMonitor->isActive())
        {
            commLinkMonitor->start();
        }
        else
        {
            commLinkMonitor->stop();
        }
    }
}

void ViewModelManager::onCaptureClicked()
{
    ImageManager *imageManager = m_earthStation->getImageManager();

    if (imageManager && m_mainScreenViewModel)
    {
        ButtonViewModel *aux = m_mainScreenViewModel->getCamSelectButton();
        if (aux)
        {
            imageManager->sendCaptureReqMessage(aux->getChecked());
        }
    }
}

void ViewModelManager::onCropClicked()
{
    ImageManager *imageManager = m_earthStation->getImageManager();

    if (imageManager)
    {
//        for (int i = 0; i < m_selectedImages.size(); ++i)
//        {
//            imageManager->selectROI(m_selectedImages.at(i));
//        }
        imageManager->selectROI(m_selectedImages.last());
    }
}


void ViewModelManager::onDownloadHQClicked(void)
{
    ImageManager *imageManager = m_earthStation->getImageManager();

    if (imageManager)
    {
        for (int i = 0; i < m_selectedImages.size(); ++i)
        {
            imageManager->sendImageCommandReqMessage(m_selectedImages.at(i), IMAGE_QUALITY_HIGH);
        }
    }
}

void ViewModelManager::onDownloadLQClicked(void)
{
    //qDebug() << "ViewModelManager::onDownloadLQClicked begin";
    ImageManager *imageManager = m_earthStation->getImageManager();

    if (imageManager)
    {
        //qDebug() << "if (imageManager) m_selectedImages.size() = " << m_selectedImages.size();

        for (int i = 0; i < m_selectedImages.size(); ++i)
        {
            imageManager->sendImageCommandReqMessage(m_selectedImages.at(i), IMAGE_QUALITY_LOW);
        }
    }
    //qDebug() << "ViewModelManager::onDownloadLQClicked end";
}

void ViewModelManager::onDeleteClicked(void)
{
    //qDebug() << "ViewModelManager::onDeleteClicked begin";
    ImageManager *imageManager = m_earthStation->getImageManager();

    if (imageManager)
    {
        //qDebug() << "if (imageManager) m_selectedImages.size() = " << m_selectedImages.size();

        for (int i = 0; i < m_selectedImages.size(); ++i)
        {
            imageManager->sendDeleteReqMessage(m_selectedImages.at(i));
        }
    }
    //qDebug() << "ViewModelManager::onDeleteClicked end";
}

void ViewModelManager::onUpdateCatalogClicked()
{
    ImageManager *imageManager = m_earthStation->getImageManager();

    if (imageManager)
    {
        imageManager->sendCatalogCommandReqMessage();
    }
}

void ViewModelManager::onAutoUpdateClicked(void)
{
    //qDebug() << "ViewModelManager::onAutoUpdateClicked(void)";
    CommLinkMonitor *commLinkMonitor = m_earthStation->getCommLinkMonitor();

    if (commLinkMonitor)
    {
        commLinkMonitor->setAutoUpdate(!commLinkMonitor->getAutoUpdate());
    }
}

void ViewModelManager::closePorts(void)
{
    if (m_earthStation)
    {
        m_earthStation->closePort(PortId::ES_OBC_PORT);
        m_earthStation->closePort(PortId::ES_IAS_PORT);
    }
    if (m_obc)
    {
        m_obc->closePort(PortId::OBC_ES_PORT);
        m_obc->closePort(PortId::OBC_IAS_PORT);
    }
    if (m_ias)
    {
        m_ias->closePort(PortId::IAS_OBC_PORT);
        m_ias->closePort(PortId::IAS_ES_PORT);
    }
}

void ViewModelManager::onErrorChanged(QString error)
{
    InfoTextViewModel *errorText = m_mainScreenViewModel->getError();

    if (errorText)
    {
        errorText->setValue(error);
    }
}

void ViewModelManager::updateButtons(CommStatus commStatus)
{
    ButtonViewModel *connectButton = m_mainScreenViewModel->getConnectButton();
    ButtonViewModel *captureButton = m_mainScreenViewModel->getCaptureButton();
    ButtonViewModel *updateCatalogButton = m_mainScreenViewModel->getUpdateCatalogButton();
    ButtonViewModel *autoUpdateButton = m_mainScreenViewModel->getSyncCatalogButton();
    ButtonViewModel *downloadHQButton = m_mainScreenViewModel->getDownloadInHQButton();
    ButtonViewModel *downloadLQButton = m_mainScreenViewModel->getDownloadSamplesButton();
    ButtonViewModel *deleteButton = m_mainScreenViewModel->getDeleteButton();
    ButtonViewModel *cropButton = m_mainScreenViewModel->getCropButton();
    ButtonViewModel *camSelectionButton = m_mainScreenViewModel->getCamSelectButton();

        switch (commStatus) {
        case CommStatus::NO_CONNECTED:
        case CommStatus::CONNECTING:
        {
            if (CommStatus::NO_CONNECTED == commStatus)
            {
                connectButton->setText("Connect");
            }
            else if (CommStatus::CONNECTING == commStatus)
            {
                connectButton->setText("Connecting");
            }
            captureButton->setEnabled(false);
            updateCatalogButton->setEnabled(false);
            autoUpdateButton->setEnabled(false);
            downloadHQButton->setEnabled(false);
            downloadLQButton->setEnabled(false);
            deleteButton->setEnabled(false);
            cropButton->setEnabled(false);
            camSelectionButton->setEnabled(false);
            break;
        }
        case CommStatus::CONNECTED:
        {
            connectButton->setText("Disconnect");
            captureButton->setEnabled(true);
            updateCatalogButton->setEnabled(true);
            autoUpdateButton->setEnabled(true);
            //fixme
//            if (m_earthStation && m_earthStation->isOpen(PortId::ES_IAS_PORT))
//            {
                downloadHQButton->setEnabled(true);
//            }
            downloadLQButton->setEnabled(true);
            deleteButton->setEnabled(true);
            cropButton->setEnabled(true);
            camSelectionButton->setEnabled(true);
        }
            break;
        default:
            break;
        }
}

void ViewModelManager::onCommStatusChanged(CommStatus commStatus)
{
    InfoTextViewModel *commStatusText = m_mainScreenViewModel->getCommStatus();
    ButtonViewModel *connectButton = m_mainScreenViewModel->getConnectButton();

    updateButtons(commStatus);
    if (commStatusText)
    {
        switch (commStatus) {
        case CommStatus::NO_CONNECTED:
            commStatusText->setValue("No connected");
            connectButton->setText("Connect");
//            connectButton->setEnabled(true);
            break;
        case CommStatus::CONNECTING:
            commStatusText->setValue("Connecting");
            connectButton->setText("Cancel");
//            connectButton->setEnabled(true);
            break;
        case CommStatus::CONNECTED:
            commStatusText->setValue("Connected");
            connectButton->setText("Disconnect");

//            connectButton->setEnabled(true);
            break;
        default:
            //qDebug() << "ERROR: Unknown comm status";
//            commStatusText->setValue("--");
//            connectButton->setText("Can't connect´");
//            connectButton->setEnabled(false);
            break;
        }
    }
}

void ViewModelManager::onAutoUpdateChanged(bool autoUpdate)
{
    //qDebug() << "ViewModelManager::onAutoUpdateChanged(autoUpdate = " << autoUpdate << ")";

    if (m_mainScreenViewModel)
    {
        ButtonViewModel *autoUpdateButton = m_mainScreenViewModel->getSyncCatalogButton();
        if (autoUpdateButton)
        {
            autoUpdateButton->setChecked(autoUpdate);
        }
    }
}

bool ViewModelManager::getAutoSync(void)
{
    //qDebug() << "ViewModelManager::getAutoSync()";
    CommLinkMonitor *commLinkMonitor;
    if (m_earthStation && (commLinkMonitor = m_earthStation->getCommLinkMonitor()))
    {
        return commLinkMonitor->getAutoUpdate();
    }
    return false;
}

void ViewModelManager::selectImage(QString id, bool select)
{
    bool ok = false;
    quint16 idInt = id.toUShort(&ok);
    if (ok)
    {
        if ((true == select) && !m_selectedImages.contains(idInt))
        {
            m_selectedImages.append(idInt);
        }
        else if ((false == select) && m_selectedImages.contains(idInt))
        {
            m_selectedImages.removeAll(idInt);
        }

        if (!m_selectedImages.isEmpty())
        {
            onImageAdded(m_selectedImages.last());
        }
        else
        {
            setImageToShow("");
        }
    }
}

bool ViewModelManager::getIASLedStatus()
{
    if (m_earthStation)
    {
        return m_earthStation->getIASLedStatus();
    }
    return false;
}

bool ViewModelManager::getOBCLedStatus()
{
    if (m_earthStation)
    {
        return m_earthStation->getOBCLedStatus();
    }
    return false;
}
