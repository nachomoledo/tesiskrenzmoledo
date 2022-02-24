#ifndef IMAGEPROPERTIESVIEWMODEL_H
#define IMAGEPROPERTIESVIEWMODEL_H

#include "ViewModel.h"
#include "ImageProperties.h"
#include <QStringList>

class ImagePropertiesViewModel : public ViewModel
{
    Q_OBJECT
    Q_PROPERTY(QStringList imagePropertyList READ getImagePropertyList CONSTANT)

private:
    QStringList m_imagePropertyList;

public:
    ImagePropertiesViewModel(ImageProperties &imageProperties);
    QStringList getImagePropertyList() const;

signals:
    void imagePropertyListChanged(void);
};

#endif // IMAGEPROPERTIESVIEWMODEL_H
