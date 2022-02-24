#include "MainScreenViewModel.h"
#include <QDebug>

#define DEBUG_TEXT_INFO
//#define ALL_PORTS

TextFieldViewModel *MainScreenViewModel::getESOBCPort() const
{
    return m_ESOBCPort;
}

TextFieldViewModel *MainScreenViewModel::getESIASPort() const
{
    return m_ESIASPort;
}

TextFieldViewModel *MainScreenViewModel::getOBCESPort() const
{
    return m_OBCESPort;
}

TextFieldViewModel *MainScreenViewModel::getOBCIASPort() const
{
    return m_OBCIASPort;
}

TextFieldViewModel *MainScreenViewModel::getIASOBCPort() const
{
    return m_IASOBCPort;
}

TextFieldViewModel *MainScreenViewModel::getIASESPort() const
{
    return m_IASESPort;
}

ButtonViewModel *MainScreenViewModel::getOpenHQImagesButton() const
{
    return m_openHQImagesButton;
}

ButtonViewModel *MainScreenViewModel::getOpenCatalogButton() const
{
    return m_openCatalogButton;
}

ButtonViewModel *MainScreenViewModel::getCamSelectButton() const
{
    return m_camSelectButton;
}

InfoTextViewModel *MainScreenViewModel::getSentLedOBCReqMessages() const
{
    return m_sentLedOBCReqMessages;
}

InfoTextViewModel *MainScreenViewModel::getReceivedLedOBCResMessages() const
{
    return m_receivedLedOBCResMessages;
}

InfoTextViewModel *MainScreenViewModel::getSentLedIASReqMessages() const
{
    return m_sentLedIASReqMessages;
}

InfoTextViewModel *MainScreenViewModel::getReceivedLedIASResMessages() const
{
    return m_receivedLedIASResMessages;
}

MainScreenViewModel::MainScreenViewModel(ImageManager *imageManager, QObject *parent)
    : AbstractScreenViewModel(parent), m_imageManager(imageManager)
{
    // TextFields
    QString separator = "\n|\n";
    QString placeHolderText = "Port";
    m_ESOBCPort = new TextFieldViewModel("ES" + separator + "OBC", placeHolderText);
    m_ESIASPort = new TextFieldViewModel("ES" + separator + "IAS", placeHolderText);
    m_OBCESPort = new TextFieldViewModel("OBC" + separator + "ES", placeHolderText);
    m_OBCIASPort = new TextFieldViewModel("OBC" + separator + "IAS", placeHolderText);
    m_IASOBCPort = new TextFieldViewModel("IAS" + separator + "OBC", placeHolderText);
    m_IASESPort = new TextFieldViewModel("IAS" + separator + "ES", placeHolderText);
    // El orden se debe a los "pares" que forman un mismo cable
    addTextField(m_ESOBCPort);
#ifdef ALL_PORTS
    addTextField(m_OBCESPort);
    addTextField(m_OBCIASPort);
    addTextField(m_IASOBCPort);
#endif
    addTextField(m_ESIASPort);
#ifdef ALL_PORTS
    addTextField(m_IASESPort);
#endif
    //Buttons
    m_connectButton = new ButtonViewModel("Connect", ButtonViewModel::COMMON);
    m_syncCatalogButton = new ButtonViewModel("Sync Catalog", ButtonViewModel::SWITCH);
    m_autodownloadCalatolgButton = new ButtonViewModel("Autodownload Catalog Images", ButtonViewModel::SWITCH);

    addButton(m_connectButton);
    addButton(m_syncCatalogButton);
    //addButton(m_autodownloadCalatolgButton);

//    connect(m_syncCatalogButton, &ButtonViewModel::clicked, this, &MainScreenViewModel::onSyncCatalogButtonClicked);
    //connect(m_autodownloadCalatolgButton, &ButtonViewModel::clicked, this, &MainScreenViewModel::onAutodownloadCalatolgClicked);

    //InfoText
    m_commStatus = new InfoTextViewModel("Comm Status");
    m_error = new InfoTextViewModel("Error");
    m_lostMessages = new InfoTextViewModel("Lost Messages");
    m_receivedMesseges = new InfoTextViewModel("Received Messages");
    m_sentMesseges = new InfoTextViewModel("Sent Messages");
    m_sentLedOBCReqMessages = new InfoTextViewModel("Sent OBC Req");
    m_receivedLedOBCResMessages = new InfoTextViewModel("Received OBC Res");
    m_sentLedIASReqMessages = new InfoTextViewModel("Sent IAS Req");
    m_receivedLedIASResMessages = new InfoTextViewModel("Received IAS Res");

    addInfoText(m_commStatus);
    addInfoText(m_error);
    addInfoText(m_lostMessages);
    addInfoText(m_receivedMesseges);
    addInfoText(m_sentMesseges);
//    addInfoText(m_sentLedOBCReqMessages);
//    addInfoText(m_receivedLedOBCResMessages);
//    addInfoText(m_sentLedIASReqMessages);
//    addInfoText(m_receivedLedIASResMessages);

    m_lostMessages->setValue("0");
    m_receivedMesseges->setValue("0");
    m_sentMesseges->setValue("0");
    m_sentLedOBCReqMessages->setValue("0");
    m_receivedLedOBCResMessages->setValue("0");
    m_sentLedIASReqMessages->setValue("0");
    m_receivedLedIASResMessages->setValue("0");
#ifdef DEBUG_TEXT_INFO
//    m_commStatus->setValue("Connected");
    //https://stackoverflow.com/questions/49029850/qml-continuouse-infinite-moving-text
    m_error->setValue("None");
#endif

    //IMAGENES

    m_captureButton = new ButtonViewModel("Capture Image", ButtonViewModel::COMMON);
    m_downloadSamplesButton = new ButtonViewModel("Download Selected Samples", ButtonViewModel::COMMON);
    m_downloadInHQButton = new ButtonViewModel("Download Selected Images in HQ", ButtonViewModel::COMMON);
    m_cropButton = new ButtonViewModel("Crop Selected Images", ButtonViewModel::COMMON);
    m_deleteButton = new ButtonViewModel("Delete Selected Images in IAS", ButtonViewModel::COMMON);
    m_openCatalogButton = new ButtonViewModel("Open LQ Images Folder", ButtonViewModel::COMMON, true);
    m_openHQImagesButton = new ButtonViewModel("Open HQ Images Folder", ButtonViewModel::COMMON, true);
    m_updateCatalogButton = new ButtonViewModel("Update Catalog", ButtonViewModel::COMMON);

    addButton(m_captureButton);
    addButton(m_downloadSamplesButton);
    addButton(m_downloadInHQButton);
    addButton(m_cropButton);
    addButton(m_deleteButton);
    addButton(m_openCatalogButton);
    addButton(m_openHQImagesButton);
    addButton(m_updateCatalogButton);

//    connect(m_captureButton, &ButtonViewModel::clicked, this, &MainScreenViewModel::onCaptureButtonClicked);
//    connect(m_downloadSamplesButton, &ButtonViewModel::clicked, this, &MainScreenViewModel::onDownloadSamplesButtonClicked);
//    connect(m_downloadInHQButton, &ButtonViewModel::clicked, this, &MainScreenViewModel::onDownloadInHQButtonClicked);
//    connect(m_cropButton, &ButtonViewModel::clicked, this, &MainScreenViewModel::onCropButtonClicked);
//    connect(m_deleteButton, &ButtonViewModel::clicked, this, &MainScreenViewModel::onDeleteButtonClicked);
//    connect(m_openCatalogButton, &ButtonViewModel::clicked, this, &MainScreenViewModel::onOpenCatalogButtonClicked);
//    connect(m_openHQImagesButton, &ButtonViewModel::clicked, this, &MainScreenViewModel::onOpenHQImagesButtonClicked);
//    connect(m_updateCatalogButton, &ButtonViewModel::clicked, this, &MainScreenViewModel::onUpdateCatalogButtonClicked);

    m_camSelectButton = new ButtonViewModel("Use webcam", ButtonViewModel::SWITCH);
    addButton(m_camSelectButton);

    m_setLedOBCButton = new ButtonViewModel("Toggle OBC Led", ButtonViewModel::COMMON);
    m_setLedIASButton = new ButtonViewModel("Toggle IAS Led", ButtonViewModel::COMMON);

#ifndef ALL_PORTS
    m_OBCESPort->setText("/dev/pts/3");
    m_OBCIASPort->setText("/dev/pts/8");
    m_IASOBCPort->setText("/dev/pts/9");
    m_IASESPort->setText("/dev/pts/6");
#endif
}

ButtonViewModel *MainScreenViewModel::getConnectButton() const
{
    return m_connectButton;
}

ButtonViewModel *MainScreenViewModel::getSyncCatalogButton() const
{
    return m_syncCatalogButton;
}

//void MainScreenViewModel::onSyncCatalogButtonClicked()
//{
//    //qDebug() << "onSyncCatalogButtonClicked!!!";
//}

//void MainScreenViewModel::onAutodownloadCalatolgClicked()
//{
//    //qDebug() << "onAutodownloadCalatolgClicked!!!";
//}

ButtonViewModel *MainScreenViewModel::getCropButton() const
{
    return m_cropButton;
}

ButtonViewModel *MainScreenViewModel::getDeleteButton() const
{
    return m_deleteButton;
}

ButtonViewModel *MainScreenViewModel::getDownloadInHQButton() const
{
    return m_downloadInHQButton;
}

ButtonViewModel *MainScreenViewModel::getDownloadSamplesButton() const
{
    return m_downloadSamplesButton;
}

ButtonViewModel *MainScreenViewModel::getUpdateCatalogButton() const
{
    return m_updateCatalogButton;
}

ButtonViewModel *MainScreenViewModel::getCaptureButton() const
{
    return m_captureButton;
}

InfoTextViewModel *MainScreenViewModel::getSentMesseges() const
{
    return m_sentMesseges;
}

InfoTextViewModel *MainScreenViewModel::getReceivedMesseges() const
{
    return m_receivedMesseges;
}

InfoTextViewModel *MainScreenViewModel::getLostMessages() const
{
    return m_lostMessages;
}

InfoTextViewModel *MainScreenViewModel::getError() const
{
    return m_error;
}

InfoTextViewModel *MainScreenViewModel::getCommStatus() const
{
    return m_commStatus;
}

//void MainScreenViewModel::onCaptureButtonClicked()
//{
//    //qDebug() << "onCaptureImageClicked!!!";
//}

//void MainScreenViewModel::onDownloadSamplesButtonClicked()
//{
//    //qDebug() << "onDownloadSamplesButtonClicked!!!";
//}

//void MainScreenViewModel::onDownloadInHQButtonClicked()
//{
//    //qDebug() << "onDownloadInHQButtonClicked!!!";
//}

//void MainScreenViewModel::onCropButtonClicked()
//{
//    //qDebug() << "onCropButtonClicked!!!";
//}

//void MainScreenViewModel::onDeleteButtonClicked()
//{
//    //qDebug() << "onDeleteButtonClicked!!!";
//}

//void MainScreenViewModel::onOpenCatalogButtonClicked()
//{
//    //qDebug() << "onOpenCatalogButtonClicked!!!";
//}

//void MainScreenViewModel::onOpenHQImagesButtonClicked()
//{
//    //qDebug() << "onOpenHQImagesButtonClicked!!!";
//}

//void MainScreenViewModel::onUpdateCatalogButtonClicked()
//{
//    //qDebug() << "onUpdateCatalogButtonClicked!!!";
//}

ButtonViewModel *MainScreenViewModel::getSetLedIASButton() const
{
    return m_setLedIASButton;
}

ButtonViewModel *MainScreenViewModel::getSetLedOBCButton() const
{
    return m_setLedOBCButton;
}

QList<QObject *> MainScreenViewModel::getCatalog() const
{
    return m_catalog;
}

void MainScreenViewModel::setCatalog(const QList<QObject *> &catalog)
{
    m_catalog = catalog;
    catalogChanged();
}

//QStringList MainScreenViewModel::qByteArrayQListToStringList(const QList<QByteArray> list)
//{
//    QStringList strings;
//    foreach (const QByteArray &item, list) {
//        strings.append(QString::fromLocal8Bit(item)); // Assuming local 8-bit.
//    }
//    return strings;
//}
