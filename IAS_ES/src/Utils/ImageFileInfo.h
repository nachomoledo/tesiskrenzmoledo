//https://retrylife.ca/blog/2020/10/01/reading-a-bitmap
//https://web.archive.org/web/20080912171714/http://www.fortunecity.com/skyscraper/windows/364/bmpffrmt.html
//https://www.oreilly.com/library/view/c-cookbook/0596007612/ch10s07.html
#ifndef IMAGEFILEINFO_H
#define IMAGEFILEINFO_H

#include <QString>

#define sizeof_BMPFileHeader 14
#define sizeof_BMPInfoHeader 12

class ImageFileInfo
{
private:
    typedef struct BMPFileHeader {
        // must always be set to 'BM' to declare that this is a .bmp-file.
        char bfType[2];
        // not used
        uint32_t bfSize;
        // not used
        uint32_t bfReserved;
        // not used
        uint32_t bfOffBits;
    } BMPFileHeader_t;

    typedef struct BMPInfoHeader {
        // not used
        uint32_t biSize;
        // specifies the width of the image, in pixels.
        int32_t biWidth;
        // specifies the height of the image, in pixels.
        int32_t biHeight;
    } BMPInfoHeader_t;

    QString m_bmpImageFullPath;
    QString m_size;
    QString m_width;
    QString m_height;
    quint64 m_timestampCreation;
    quint64 m_timestampLastMod;

    bool isValid(BMPFileHeader &bmpFileHeader) const;

public:
    ImageFileInfo(const QString &bmpImageFullPath);
    QString bmpImageFullPath() const;
    void setBmpImageFullPath(const QString &bmpImageFullPath);
    void loadBMPImage(const QString &bmpImageFullPath);
    void printImageFileInfo();
    QString size() const;
    QString width() const;
    QString height() const;
    quint64 timestampCreation() const;
    quint64 timestampLastMod() const;
};

#endif // IMAGEFILEINFO_H
