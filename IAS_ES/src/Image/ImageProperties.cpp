#include "ImageProperties.h"
#include "Operators.h"
#include <QDebug>

ImageProperties::ImageProperties()
    : m_id(0), m_size("0"), m_width("0"), m_height("0"), m_timestamp(0)
{

}

ImageProperties::ImageProperties(quint16 id, QString size, QString width, QString height, quint64 timestamp)
    : m_id(id), m_size(size), m_width(width), m_height(height), m_timestamp(timestamp)
{

}


quint16 ImageProperties::getId() const
{
    return m_id;
}

QString ImageProperties::getSize() const
{
    return m_size;
}

QString ImageProperties::getWidth() const
{
    return m_width;
}

QString ImageProperties::getHeight() const
{
    return m_height;
}

quint64 ImageProperties::getTimestamp() const
{
    return m_timestamp;
}

QByteArray ImageProperties::getPropertiesQBA(void)
{
    QByteArray array;
    array << quint64(getSize().toULongLong());
    array << quint16(getWidth().toUShort());
    array << quint16(getHeight().toUShort());
    array << quint64(getTimestamp());
    return array;
}

QString ImageProperties::getPropertiesQS(void)
{
    QString qs;
    qs = "Size: " + getSize() + ", Width: " + getWidth() + ", Height " + getHeight() + ", Timestamp: " + QString::number(getTimestamp());
    return qs;
}
