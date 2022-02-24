#include "ImageDataBase.h"
#include "Defines.h"
#include "Files.h"
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QImage>
#include "ImageFileInfo.h"

ImageDataBase::ImageDataBase(QString imageBasePath, QString csvFile)
    : m_imageDBPath(imageBasePath + "/db/"), m_imageHQPath(imageBasePath + "/hq/"), m_imageLQPath(imageBasePath + "/lq/"), m_csvFile(csvFile)
{
    /* TODO: La ET debería pedir el catálogo al encenderse (si puede, si no, trabaja con catálogo viejo, indicar con warning) */
/* TODO: Ver si hace falta, pueden estar sincronizados siempre por el mecanismo de update automatico */
    checkExistingCSVFile();
    setLastChecksum(fileChecksum(m_imageDBPath+m_csvFile));
    connect(this, &ImageDataBase::imageMapChanged, this, [=]{setLastChecksum(fileChecksum(m_imageDBPath+m_csvFile));});
    //^printDataBase();
}

QByteArray ImageDataBase::getLastChecksum() const
{
    return m_lastChecksum;
}

void ImageDataBase::setLastChecksum(const QByteArray &lastChecksum)
{
    m_lastChecksum = lastChecksum;
}

void ImageDataBase::setImageMap(const QMap<unsigned short, ImageProperties *> &imageMap)
{
    m_imageMap = imageMap;
    emit imageMapChanged();
}

void ImageDataBase::clearImageMapAux(void)
{
    m_imageMapAux.clear();
}

void ImageDataBase::buildCatalog()
{
    QMap<unsigned short, ImageProperties*> imageMap;
    //qDebug() << "ImageDataBase::buildCatalog() begin";
    QDir directory(m_imageHQPath);
    QStringList images = directory.entryList(QStringList() << "*.bmp" << "*.BMP", QDir::Files);
    //qDebug() << "ImageDataBase::buildCatalog() images = " << images;

    QFile file(m_imageDBPath+m_csvFile);

    if (!file.open(QIODevice::ReadWrite | QIODevice::Truncate))
    {
        //qDebug() << "CSV FILE ALREADY EXISTS (" << m_imageDBPath+m_csvFile << "): " << file.errorString();
    }
    QTextStream out(&file);

    for (int i = 0; i < images.size(); ++i)
    {
        QString filename = m_imageHQPath+images.at(i);
        //qDebug() << "Image filename    :" << filename.toStdString().c_str();
        ImageFileInfo imageFileInfo(filename);
        imageFileInfo.printImageFileInfo();
        QString name = images.at(i);
        name.chop(4);
        bool ok = false;
        int id = name.toUInt(&ok);
        if (ok)
        {
            imageMap.insert(id, new ImageProperties(id, imageFileInfo.size(), imageFileInfo.width(), imageFileInfo.height(), imageFileInfo.timestampCreation() ));
        }
    }

    // se usa un mapa auxiliar para que agregar las imagenes en "orden de int" y no en "orden de string"
    QMapIterator<unsigned short, ImageProperties*> i(imageMap);
    while (i.hasNext()) {
        i.next();
        ImageProperties* img = i.value();
        if (img)
        {
            out << QString::number(img->getId()) << "," << img->getSize() << "," << img->getWidth()  << "," << img->getHeight() << "," << img->getTimestamp() << "\n";
        }
    }

    file.close();
    //qDebug() << "ImageDataBase::buildCatalog() end";
}

QString ImageDataBase::getImageName(unsigned short id) const
{
    if (m_imageMap.contains(id))
    {
        //return m_imageMap.value(id)->getId();
        return QString::number(id);

    }
    else
    {
        return "";
    }
}

QString ImageDataBase::getImageNameWithExtension(unsigned short id, QString extension) const
{
    if (m_imageMap.contains(id))
    {
        //return m_imageMap.value(id)->getName() + HIGH_QUALITY_EXTENSION;
        return QString::number(id) + extension;
    }
    else
    {
        return "";
    }
}

QString ImageDataBase::getImageBasePathAndNameWithExtension(unsigned short id, QString extension) const
{
    //qDebug() << "ImageDataBase::getImageBasePathAndNameWithExtension getImageNameWithExtension() = |" << getImageNameWithExtension(id, extension) << "|";

    if (HIGH_QUALITY_EXTENSION == extension)
    {
        return getImageHQPath() + getImageNameWithExtension(id, extension);
    }
    else if (LOW_QUALITY_EXTENSION == extension)
    {
        return getImageLQPath() + getImageNameWithExtension(id, extension);
    }

    return "";
}


QMap<unsigned short, ImageProperties *> ImageDataBase::getImageMap() const
{
    return m_imageMap;
}

QMap<unsigned short, ImageProperties *> ImageDataBase::getImageMapAux() const
{
    return m_imageMapAux;
}

/*! \brief Verifica la existencia del catálogo. Si no existe, crea uno vacío.
 *  \return void
*/
void ImageDataBase::checkExistingCSVFile()
{
    QFile file(m_imageDBPath+m_csvFile);

    if (!file.open(QIODevice::NewOnly))
    {
        //qDebug() << "CSV FILE ALREADY EXISTS (" << m_imageDBPath+m_csvFile << "): " << file.errorString();
    }

    file.close();
}


void ImageDataBase::loadCSVFile()
{
    //qDebug() << "ImageDataBase::loadCSVFile()";
    QFile file(m_imageDBPath+m_csvFile);
    if (!file.open(QIODevice::ReadOnly)) {
        //qDebug() << "ERROR READING FILE " << m_imageDBPath+m_csvFile << ": " << file.errorString();
        return;
    }

    //qDebug() << "File " << m_imageDBPath+m_csvFile << " opened successfuly";

    QStringList wordList;
    bool ok1 = false, ok2 = false;
    QByteArray line;
    while (!file.atEnd()) {
        line = file.readLine();
        //qDebug() << "line = " << line;
        wordList = Files::processLine(line);
        //qDebug() << "wordList = " << wordList;
        if (wordList.size() != 5)
        {
            //qDebug() << "Image Row Size failed";
        }
        else
        {
            addImageToMap(wordList.at(0).toUInt(&ok1), wordList.at(1), wordList.at(2), wordList.at(3), wordList.at(4).toULongLong(&ok2));
        }
        if ((!ok1) || (!ok2)) {
            //qDebug() << "Parsing image ID failed";
        }
        wordList.clear();
    }
    file.close();
}

void ImageDataBase::addImageToMap(unsigned short id, QString size, QString width, QString height, quint64 timestamp)
{
    m_imageMap.insert(id, new ImageProperties(id, size, width, height, timestamp));
    //qDebug() << "ImageDataBase::addImageToMap emit imageMapChanged()";
    emit imageMapChanged();
}

void ImageDataBase::addImageToMapAux(unsigned short id, QString size, QString width, QString height, quint64 timestamp)
{
    m_imageMapAux.insert(id, new ImageProperties(id, size, width, height, timestamp));
}

//FIXME: Utilizar ids incrementales.
//TODO: La función que llame a esta función tiene que primero abrir el csv en lectura para sacar el nextId y pasarlo
void ImageDataBase::registerImage(unsigned short id, QString size, QString width, QString height, quint64 timestamp)
{
    if (m_imageMap.contains(id))
    {
        //qDebug() << "Image ID " << id << "is already in map";
        /* TODO: retornar código de error */
    }

    QFile file(m_imageDBPath+m_csvFile);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    {
        //qDebug() << "ERROR READING FILE " << m_imageDBPath+m_csvFile << ": " << file.errorString();
        /* TODO: retornar código de error */
    }

    //qDebug() << "File " << m_imageDBPath+m_csvFile << " opened successfuly";

    QTextStream out(&file);
    out << QString::number(id) << "," << size << "," << width << "," << height << "," << timestamp << "\n";
    file.close();

    addImageToMap(id, size, width, height, timestamp);
}

void ImageDataBase::registerImage(QList<ImageProperties> list)
{
    for (int i = 0; i < list.size(); i++)
    {
        ImageProperties prop = list.at(i);
        registerImage(prop.getId(), prop.getSize(), prop.getWidth(), prop.getHeight(), prop.getTimestamp());
    }
}

void ImageDataBase::printDataBase()
{
    QMapIterator<unsigned short, ImageProperties*> i(m_imageMap);
    while (i.hasNext()) {
        i.next();
        ImageProperties *img = i.value();
        //qDebug() << "Image " << i.key() << ": size = " << img->getSize() << ", width = " << img->getWidth() << ", height = " << img->getHeight();
    }
}

// FIXME: esto supone que los paquetes llegan en orden.
// TODO: detectar condiciones de error y recuperar el archivo
/* El CSV siempre se debería sobrescribir y no, por ejemplo, pedir el catálogo a partir de cierto ID, para evitar problemas al borrar IDs intermedios. */
void ImageDataBase::buildCatalogET(unsigned short id, QString size, QString width, QString height, quint64 timestamp, unsigned short packetNumber, unsigned short totalPackets)
{
    addImageToMapAux(id, size, width, height, timestamp);

    if (packetNumber == totalPackets)
    {
        setImageMap(m_imageMapAux);

        QFile file(m_imageDBPath+m_csvFile);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            //qDebug() << "ERROR READING FILE " << m_imageDBPath+m_csvFile << ": " << file.errorString();
            return;
        }

        //qDebug() << "File " << m_imageDBPath+m_csvFile << " opened successfuly";

        QTextStream out(&file);

        QMapIterator<unsigned short, ImageProperties*> i(m_imageMap);
        while (i.hasNext()) {
            i.next();
            ImageProperties *img = i.value();
            out << i.key() << "," << img->getSize() << "," << img->getWidth() << "," << img->getHeight() << "," << img->getTimestamp() << "\n";
        }

        file.close();
        setLastChecksum(fileChecksum(m_imageDBPath+m_csvFile));
    }
}

void ImageDataBase::createCatalogBackup(void)
{
    QFile::copy(m_imageDBPath+m_csvFile, m_imageDBPath+m_csvFile + BACKUP_EXTENSION);
}

void ImageDataBase::deleteFromImageMap(quint16 id)
{
    m_imageMap.remove(id);
    //qDebug() << "ImageDataBase::deleteFromImageMap emit imageMapChanged()";
    emit imageMapChanged();
}

void ImageDataBase::deleteFromImageMap(QList<quint16> idList)
{
    for (int i =0; i < idList.size(); i++)
    {
        deleteFromImageMap(idList.at(i));
    }
}

void ImageDataBase::deleteFromDisk(quint16 id)
{
    static QDir dirHQ(m_imageHQPath);
    static QDir dirLQ(m_imageLQPath);
    QString imageJPG = getImageName(id) + LOW_QUALITY_EXTENSION;
    QString imageBMP = getImageName(id) + HIGH_QUALITY_EXTENSION;

    //qDebug() << "dir = " << dirHQ.path();
    //qDebug() << "dir = " << dirLQ.path();
    //qDebug() << "imageJPG = " << imageJPG;
    //qDebug() << "imageBMP = " << imageBMP;

    if(dirLQ.remove(imageJPG))
    {
        //qDebug() << "imageJPG removed succesfully";
    }
    else
    {
        //qDebug() << "remove imageJPG failed";
    }

    if(dirHQ.remove(imageBMP))
    {
        //qDebug() << "imageBMP removed succesfully";
    }
    else
    {
        //qDebug() << "remove imageBMP failed";
    }
}


void ImageDataBase::deleteFromCSVFile(QList<quint16> idList)
{
    QFile file(m_imageDBPath+m_csvFile);
    if (!file.open(QIODevice::ReadOnly)) {
        //qDebug() << "ERROR OPENING FILE " << m_imageDBPath+m_csvFile << ": " << file.errorString();
        return;
    }

    QStringList stringList;
    bool ok;

    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        QByteArray idArray = line.split(',').first();
        quint16 id = idArray.toUInt(&ok);

        if (!ok) {
            //qDebug() << "Parsing image ID failed";
        }

        if (!idList.contains(id))
        {
            stringList.append(line);
        }
    }

    file.close();

    if (!file.open(QIODevice::WriteOnly)) {
        //qDebug() << "ERROR OPENING FILE " << m_imageDBPath+m_csvFile << ": " << file.errorString();
        return;
    }

    QTextStream out(&file);

    for (int i = 0; i < stringList.size(); i++)
    {
        out << stringList.at(i);
    }

    file.close();
}

QString ImageDataBase::getImageDBPath() const
{
    return m_imageDBPath;
}

QString ImageDataBase::getImageHQPath() const
{
    return m_imageHQPath;
}

QString ImageDataBase::getImageLQPath() const
{
    return m_imageLQPath;
}

QByteArray ImageDataBase::fileChecksum(const QString &fileName,
                                       QCryptographicHash::Algorithm hashAlgorithm)
{
    QFile f(fileName);

    if (f.open(QFile::ReadOnly))
    {
        QCryptographicHash hash(hashAlgorithm);

        if (hash.addData(&f))
        {
            return hash.result();
        }
    }

    return QByteArray();
}

bool ImageDataBase::isDownloaded(unsigned short id, QString extension)
{
    QString image = getImageBasePathAndNameWithExtension(id, extension);
    //qDebug() << "ImageDataBase::isDownloaded image = " << image;
    if (QFile::exists(image))
    {
        //qDebug() << "ImageDataBase::isDownloaded retrun true";
        return true;
    }
    //qDebug() << "ImageDataBase::isDownloaded retrun false";
    return false;
}


// Clase que represnta imagen con sus propiedades
// qhash de id, clase que representa imagen
// constructor de data base accede a un csv en modo lectura y llena el qhash
// crear metodo "write new entry" para pasar propiedades, escribir en el csv y en el qhash
// ver como capturar el ultimo id despues del load y agregar imagenes nuevas con el id siguiente
