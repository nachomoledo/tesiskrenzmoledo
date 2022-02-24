#ifndef SPIPORTMANAGER_H
#define SPIPORTMANAGER_H

#include <QByteArray>
#include <QString>
#include <linux/spi/spidev.h>

class SPIPortManager
{
private:
    int m_fd;
    QString m_portName;
    unsigned int m_speed;

public:
    SPIPortManager(const QString &portName, const unsigned int speed);
    void write(QByteArray &writeData);
    void openPort();
};

#endif // SPIPORTMANAGER_H
