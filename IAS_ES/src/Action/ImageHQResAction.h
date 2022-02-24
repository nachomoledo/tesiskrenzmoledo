#ifndef IMAGEHQRESACTION_H
#define IMAGEHQRESACTION_H

#include "Action.h"
#include <QByteArray>
#include <QString>

#define DATAMAX 118

class ImageHQResAction : public Action
{
private:
    QString m_imagePath;
    int m_packetNumber;
    int m_totalPackets;
    QByteArray m_imageData;

public:
    ImageHQResAction(QString imagePath, int packetNumber, int totalPackets, QByteArray imageData);
    void execute(void) override;
};

#endif // IMAGEHQRESACTION_H
