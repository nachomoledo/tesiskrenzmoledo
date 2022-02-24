#include "SPIPortManager.h"
#include "PacketBuilder.h"
#include <QDebug>
#include <sys/ioctl.h>
#include <fcntl.h>

SPIPortManager::SPIPortManager(const QString &portName, const unsigned int speed)
    : m_portName(portName), m_speed(speed)
{

}

void SPIPortManager::write(QByteArray &writeData)
{
//    qDebug() << "SPIPortManager::write BEFORE " << writeData.toHex();
    writeData = PacketBuilder::addEscapeSequences(writeData);
//    qDebug() << "SPIPortManager::write AFTER " << writeData.toHex();
    //Estructura que contendrá los valores a recibir y enviar.
    struct spi_ioc_transfer spi;
    memset (&spi, 0, sizeof (spi));

    spi.tx_buf        = (unsigned long) writeData.constData();
    //Longitud de los datos.
    spi.len           = writeData.size();

    ioctl (m_fd, SPI_IOC_MESSAGE(1), &spi);
}

void SPIPortManager::openPort()
{
    //Abre el puerto SPI.
    m_fd = open (m_portName.toStdString().c_str(), O_RDWR);
    //Establece velcidad de enlace SPI.
    ioctl (m_fd, SPI_IOC_WR_MAX_SPEED_HZ, &m_speed);
}
