#ifndef IMAGEACQUISITIONSYSTEM_H
#define IMAGEACQUISITIONSYSTEM_H

#include "Computer.h"
#include "ImageManager.h"

class ImageAcquisitionSystem : public Computer
{
private:
    ImageManager *m_imageManager;
    bool m_led;
public:
    ImageAcquisitionSystem(QString name, QString basePath);
    bool getLed() const;
    void setLed(bool led);
};

#endif // IMAGEACQUISITIONSYSTEM_H
