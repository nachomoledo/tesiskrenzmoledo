#ifndef IMAGEDATABASE_H
#define IMAGEDATABASE_H

#include "ImageProperties.h"
#include <QMap>
#include <QObject>
#include <QCryptographicHash>

class ImageDataBase : public QObject
{
    Q_OBJECT
    friend class DeleteReqAction;
    friend class CatalogReqAction;
    friend class KeepaliveReqAction;

private:
    /* Variable para indicarle a la ET si tiene sincronizada la DB o no
     - TRUE: DB sincronizada
     - FALSE: DB necesita ser actualizada

     Deberia ser false cuando:
     - Se agrega una imagen (foto nueva o recorte)
     - Se borra una imagen

     Debería ser true cuando:
     - Se manda el último mensaje del CSV

     TODO: poner en false al sacar foto
*/
    const QString m_imageDBPath;
    const QString m_imageHQPath;
    const QString m_imageLQPath;
    const QString m_csvFile;
    QByteArray m_lastChecksum;
    QByteArray fileChecksum(const QString &fileName, QCryptographicHash::Algorithm hashAlgorithm = QCryptographicHash::Keccak_512);
    void setLastChecksum(const QByteArray &lastChecksum);
    //-----------------------------
    QMap<unsigned short, ImageProperties*> m_imageMap;
    QMap<unsigned short, ImageProperties*> m_imageMapAux;


public:
    ImageDataBase(QString imageBasePath, QString csvFile);
    void buildCatalog(void);


    void addImageToMap(unsigned short id, QString size, QString width, QString height, quint64 timestamp);
    void addImageToMapAux(unsigned short id, QString size, QString width, QString height, quint64 timestamp);
    QString getImageName(unsigned short id) const;
    QString getImageNameWithExtension(unsigned short id, QString extension) const;
    QString getImageBasePathAndNameWithExtension(unsigned short id, QString extension) const;
    void loadCSVFile(void);
    void printDataBase(void);
    void registerImage(unsigned short id, QString size, QString width, QString height, quint64 timestamp);
    void registerImage(QList<ImageProperties>);
    QMap<unsigned short, ImageProperties *> getImageMap() const;
    void buildCatalogET(unsigned short id, QString size, QString width, QString height, quint64 timestamp, unsigned short packetNumber, unsigned short totalPackets);
    void createCatalogBackup(void);
    QMap<unsigned short, ImageProperties *> getImageMapAux() const;
    void deleteFromImageMap(quint16 id);
    void deleteFromImageMap(QList<quint16> idList);
    void deleteFromCSVFile(QList<quint16> idList);
    void deleteFromDisk(quint16 id);
    void checkExistingCSVFile();

    QByteArray getLastChecksum() const;

    void setImageMap(const QMap<unsigned short, ImageProperties *> &imageMap);
    void clearImageMapAux(void);
    bool isDownloaded(unsigned short id, QString extension);
    QString getImageDBPath() const;

    QString getImageHQPath() const;

    QString getImageLQPath() const;

signals:
    void imageMapChanged(void);
};

#endif // IMAGEDATABASE_H
