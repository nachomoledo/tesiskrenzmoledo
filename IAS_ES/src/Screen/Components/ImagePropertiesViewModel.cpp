#include "ImagePropertiesViewModel.h"
#include <QDateTime>

QStringList ImagePropertiesViewModel::getImagePropertyList() const
{
    return m_imagePropertyList;
}

ImagePropertiesViewModel::ImagePropertiesViewModel(ImageProperties &imageProperties)
{
    m_imagePropertyList.append(QString::number(imageProperties.getId()));
    m_imagePropertyList.append(imageProperties.getSize());
    m_imagePropertyList.append(imageProperties.getWidth());
    m_imagePropertyList.append(imageProperties.getHeight());
    QDateTime qDateTime;
    qDateTime.setSecsSinceEpoch(imageProperties.getTimestamp());
    m_imagePropertyList.append(qDateTime.toString());
}
