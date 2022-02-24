#include "ImageFileInfo.h"
#include <stdint.h>
#include <sys/stat.h>
#include <QDebug>

ImageFileInfo::ImageFileInfo(const QString &bmpImageFullPath)
{
    loadBMPImage(bmpImageFullPath);
}

void ImageFileInfo::loadBMPImage(const QString &bmpImageFullPath)
{
    BMPFileHeader_t bmpFile;
    BMPInfoHeader_t bmpInfo;
    struct stat fileInfo;

    setBmpImageFullPath(bmpImageFullPath);
    FILE *fp = fopen(bmpImageFullPath.toStdString().c_str(), "rb");
    if (!fp) {
        //qDebug() << "Can't open file.";
        return;
    }
    fread(&bmpFile, sizeof_BMPFileHeader, 1, fp);
    fread(&bmpInfo, sizeof_BMPInfoHeader, 1, fp);
    if (stat(bmpImageFullPath.toStdString().c_str(), &fileInfo) != 0) {  // Use stat() to get the info
       //qDebug() << "Error: " << strerror(errno);
       fclose(fp);
       return;
    }

    if(!isValid(bmpFile))
    {
        //qDebug() << "Invalid bmp file header.";
        fclose(fp);
        return;
    }
    else
    {
        //qDebug() << "Valid bmp file header.";
        m_size = QString::number(fileInfo.st_size);
        m_width = QString::number(bmpInfo.biWidth);
        m_height = QString::number(bmpInfo.biHeight);
        m_timestampCreation = fileInfo.st_ctime;
        m_timestampLastMod = fileInfo.st_mtime;
    }

    if(isValid(bmpFile))
    {
        //qDebug() << "Valid bmp file header.";
        m_size = QString::number(fileInfo.st_size);
        m_width = QString::number(bmpInfo.biWidth);
        m_height = QString::number(bmpInfo.biHeight);
        m_timestampCreation = fileInfo.st_ctime;
        m_timestampLastMod = fileInfo.st_mtime;
    }
    else
    {
        //qDebug() << "Invalid bmp file header.";
        fclose(fp);
        return;
    }
    fclose(fp);
}

QString ImageFileInfo::size() const
{
    return m_size;
}

QString ImageFileInfo::width() const
{
    return m_width;
}

QString ImageFileInfo::height() const
{
    return m_height;
}

quint64 ImageFileInfo::timestampCreation() const
{
    return m_timestampCreation;
}

quint64 ImageFileInfo::timestampLastMod() const
{
    return m_timestampLastMod;
}

bool ImageFileInfo::isValid(BMPFileHeader &bmpFileHeader) const
{
    //qDebug() << "bmpFileHeader.bfType[0] = " << bmpFileHeader.bfType[0] << ": " << "bmpFileHeader.bfType[1]) = " << bmpFileHeader.bfType[1] << "bmpFileHeader.bfReserved = " << bmpFileHeader.bfReserved;
    if (('B' == bmpFileHeader.bfType[0])
            && ('M' == bmpFileHeader.bfType[1])
            /*&& (0 == bmpFileHeader.bfReserved)*/)
    {
        return true;
    }
    else
    {
        return false;
    }
}

QString ImageFileInfo::bmpImageFullPath() const
{
    return m_bmpImageFullPath;
}

void ImageFileInfo::setBmpImageFullPath(const QString &bmpImageFullPath)
{
    m_bmpImageFullPath = bmpImageFullPath;
}

void ImageFileInfo::printImageFileInfo()
{
    //qDebug() << "Image " << m_bmpImageFullPath << ": " << "size = " << m_size << "width = " << m_width << "height = " << m_height << "creationTime = " << m_timestampCreation << "lastModTime = " << m_timestampLastMod;
}
