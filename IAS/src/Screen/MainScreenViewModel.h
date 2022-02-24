#ifndef MAINSCREENVIEWMODEL_H
#define MAINSCREENVIEWMODEL_H

#include "AbstractScreenViewModel.h"
#include "ImageManager.h"

class MainScreenViewModel : public AbstractScreenViewModel
{   
    Q_OBJECT
    Q_PROPERTY(QList<QObject*> catalogModel READ getCatalog WRITE setCatalog NOTIFY catalogChanged)

private:
    // Text Fields
    TextFieldViewModel *m_ESOBCPort;
    TextFieldViewModel *m_ESIASPort;
    TextFieldViewModel *m_OBCESPort;
    TextFieldViewModel *m_OBCIASPort;
    TextFieldViewModel *m_IASOBCPort;
    TextFieldViewModel *m_IASESPort;
    // Botones
    ButtonViewModel *m_connectButton;
    ButtonViewModel *m_syncCatalogButton;
    ButtonViewModel *m_autodownloadCalatolgButton;
    ButtonViewModel *m_camSelectButton;
    void onSyncCatalogButtonClicked(void);
    void onAutodownloadCalatolgClicked(void);
    //InfoTExt
    InfoTextViewModel *m_commStatus;
    InfoTextViewModel *m_error;
    InfoTextViewModel *m_lostMessages;
    InfoTextViewModel *m_receivedMesseges;
    InfoTextViewModel *m_sentMesseges;
    InfoTextViewModel *m_sentLedOBCReqMessages;
    InfoTextViewModel *m_receivedLedOBCResMessages;
    InfoTextViewModel *m_sentLedIASReqMessages;
    InfoTextViewModel *m_receivedLedIASResMessages;
    //IMAGENES
    // Botones
    ButtonViewModel *m_captureButton;
    ButtonViewModel *m_downloadSamplesButton;
    ButtonViewModel *m_downloadInHQButton;
    ButtonViewModel *m_cropButton;
    ButtonViewModel *m_deleteButton;
    ButtonViewModel *m_openCatalogButton;
    ButtonViewModel *m_openHQImagesButton;
    ButtonViewModel *m_updateCatalogButton;
//    void onCaptureButtonClicked(void);
//    void onDownloadSamplesButtonClicked(void);
//    void onDownloadInHQButtonClicked(void);
//    void onCropButtonClicked(void);
//    void onDeleteButtonClicked(void);
//    void onOpenCatalogButtonClicked(void);
//    void onOpenHQImagesButtonClicked(void);
//    void onUpdateCatalogButtonClicked(void);
    //Botones
    ButtonViewModel *m_setLedOBCButton;
    ButtonViewModel *m_setLedIASButton;
    // Show CSV
    QList<QObject*> m_catalog;
    ImageManager *m_imageManager;
//    QStringList qByteArrayQListToStringList(const QList<QByteArray> list);
public:
    MainScreenViewModel(ImageManager *imageManager, QObject *parent = nullptr);
    ButtonViewModel *getConnectButton() const;
    InfoTextViewModel *getCommStatus() const;
    InfoTextViewModel *getError() const;
    InfoTextViewModel *getLostMessages() const;
    InfoTextViewModel *getReceivedMesseges() const;
    InfoTextViewModel *getSentMesseges() const;
    InfoTextViewModel *getSentLedOBCReqMessages() const;
    InfoTextViewModel *getReceivedLedOBCResMessages() const;
    InfoTextViewModel *getSentLedIASReqMessages() const;
    InfoTextViewModel *getReceivedLedIASResMessages() const;
    QList<QObject *> getCatalog() const;
    void setCatalog(const QList<QObject *> &catalog);
    ButtonViewModel *getCaptureButton() const;
    ButtonViewModel *getUpdateCatalogButton() const;
    ButtonViewModel *getSyncCatalogButton() const;
    ButtonViewModel *getDownloadSamplesButton() const;
    ButtonViewModel *getDownloadInHQButton() const;
    ButtonViewModel *getDeleteButton() const;
    ButtonViewModel *getCropButton() const;
    ButtonViewModel *getSetLedOBCButton() const;
    ButtonViewModel *getSetLedIASButton() const;
    TextFieldViewModel *getESOBCPort() const;
    TextFieldViewModel *getESIASPort() const;
    TextFieldViewModel *getOBCESPort() const;
    TextFieldViewModel *getOBCIASPort() const;
    TextFieldViewModel *getIASOBCPort() const;
    TextFieldViewModel *getIASESPort() const;

    ButtonViewModel *getOpenHQImagesButton() const;

    ButtonViewModel *getOpenCatalogButton() const;

    ButtonViewModel *getCamSelectButton() const;



signals:
    void catalogChanged(void);
};

#endif // MAINSCREENVIEWMODEL_H
