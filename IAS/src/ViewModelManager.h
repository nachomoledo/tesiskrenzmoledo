#ifndef VIEWMODELMANAGER_H
#define VIEWMODELMANAGER_H

#include "MainScreenViewModel.h"
#include "ScreenProperties.h"
#include "EarthStation.h"
#include "ImageAcquisitionSystem.h"
#include "OnBoardComputer.h"

/* Hay que pasarle en el constructor lo necesario para crear los view models que se expone a QML */
class ViewModelManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(AbstractScreenViewModel* mainScreenViewModel READ getMainScreenViewModel CONSTANT)
    Q_PROPERTY(ScreenProperties* screenProperties READ getScreenProperties CONSTANT)
    Q_PROPERTY(bool autoSync READ getAutoSync NOTIFY autoSyncChanged)
    Q_PROPERTY(QString imageToShow READ getImageToShow NOTIFY imageToShowChanged)
    Q_PROPERTY(ButtonViewModel* setLedOBCButton READ getSetLedOBCButton CONSTANT)
    Q_PROPERTY(ButtonViewModel* setLedIASButton READ getSetLedIASButton CONSTANT)
    Q_PROPERTY(bool iasLedStatus READ getIASLedStatus NOTIFY iasLedStatusChanged)
    Q_PROPERTY(bool obcLedStatus READ getOBCLedStatus NOTIFY obcLedStatusChanged)

private:
    MainScreenViewModel *m_mainScreenViewModel;
    ScreenProperties *m_screenProperties;
    EarthStation *m_earthStation;
    ImageAcquisitionSystem *m_ias;
    OnBoardComputer *m_obc;
    QList<quint16> m_selectedImages;
    QString m_imageToShow;
    void onESOBCPortChanged(QString text);
    void onESIASPortChanged(QString text);
    void onOBCESPortChanged(QString text);
    void onOBCIASPortChanged(QString text);
    void onIASOBCPortChanged(QString text);
    void onIASESPortChanged(QString text);
    void onConnectedClicked(void);
    void onCaptureClicked(void);
    void onDownloadHQClicked(void);
    void onDownloadLQClicked(void);
    void onDeleteClicked(void);
    void onCropClicked(void);
    void onUpdateCatalogClicked(void);
    void onAutoUpdateClicked(void);
    void onCommStatusChanged(CommStatus status);
    void onAutoUpdateChanged(bool autoUpdate);
    void onErrorChanged(QString error);
    void onPortOpened(PortId portId);
    void onLostMessagesChanged(quint32 total);
    void onSentMessagesChanged(quint32 total);
    void onReceivedMessagesChanged(quint32 total);
    void buildCatalog(QMap<unsigned short, ImageProperties *> map);
    bool getIASLedStatus(void);
    bool getOBCLedStatus(void);
    void updateButtons(CommStatus commStatus);

public:
    ViewModelManager(EarthStation *earthStation, ImageAcquisitionSystem *ias, OnBoardComputer *obc);
    MainScreenViewModel *getMainScreenViewModel() const;
    ScreenProperties *getScreenProperties() const;
    bool getAutoSync(void);
    void closePorts(void);
    Q_INVOKABLE void selectImage(QString id, bool select);

    QString getImageToShow() const;
    ButtonViewModel* getSetLedOBCButton();
    ButtonViewModel* getSetLedIASButton();

    void onImageAdded(int id);

    void setImageToShow(const QString &imageToShow);

signals:
    void autoSyncChanged(void);
    void imageToShowChanged(void);
    void iasLedStatusChanged(void);
    void obcLedStatusChanged(void);
};

#endif // VIEWMODELMANAGER_H
