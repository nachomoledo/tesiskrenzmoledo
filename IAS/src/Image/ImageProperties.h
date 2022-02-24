#ifndef IMAGEPROPERTIES_H
#define IMAGEPROPERTIES_H

#include <QString>

class ImageProperties
{
private:
    quint16 m_id;
    QString m_size;
    QString m_width;
    QString m_height;
    quint64 m_timestamp;
public:
    ImageProperties();
    ImageProperties(quint16 id, QString size, QString width, QString height, quint64 timestamp);
    quint16 getId() const;
    QString getSize() const;
    QString getWidth() const;
    QString getHeight() const;
    QByteArray getPropertiesQBA(void);
    quint64 getTimestamp() const;
    QString getPropertiesQS(void);
};

#endif // IMAGEPROPERTIES_H
