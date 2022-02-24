#ifndef IMAGELQRESACTION_H
#define IMAGELQRESACTION_H

#include "Action.h"
#include <QByteArray>
#include <QString>

#define DATAMAX 118

class ImageLQResAction : public Action
{
private:
    QString m_imagePath;
    int m_packetNumber;
    int m_totalPackets;
    QByteArray m_imageData;

public:
    ImageLQResAction(QString imagePath, int packetNumber, int totalPackets, QByteArray imageData);
    void execute(void) override;
};

#endif // IMAGELQRESACTION_H
