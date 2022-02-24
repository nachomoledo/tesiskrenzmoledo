#include "SerialPortManager.h"
#include "Protocol/PacketValidator.h"
#include "PacketBuilder.h"
#include "Operators.h"
#include <QDebug>

//TODO: mandar paquetes de get image response por otro puerto

SerialPortManager::SerialPortManager(QString name, const int &baudRate, QObject *parent) : QObject(parent), m_name(name)
{
//    m_lostMessages = 0;
//    m_sentMessages = 0;
//    m_receivedMessages = 0;
    m_bytesWritten = 0;
    m_serialPort.setBaudRate(baudRate);
    m_serialPort.setDataBits(QSerialPort::Data8);
    m_serialPort.setParity(QSerialPort::NoParity);
    m_serialPort.setStopBits(QSerialPort::OneStop);
    m_serialPort.setFlowControl(QSerialPort::NoFlowControl);


    m_timerW.setSingleShot(true);
    connect(&m_serialPort, &QSerialPort::bytesWritten,
            this, &SerialPortManager::handleBytesWritten);
    connect(&m_serialPort, &QSerialPort::errorOccurred,
            this, &SerialPortManager::handleError);
    connect(&m_timerW, &QTimer::timeout, this, &SerialPortManager::handleTimeoutW);
    connect(&m_serialPort, &QSerialPort::readyRead, this, &SerialPortManager::handleReadyRead);
    connect(&m_timerR, &QTimer::timeout, this, &SerialPortManager::handleTimeoutR);
    m_timerR.setInterval(500);
//    m_timerR.start(5000);
}

//void SerialPortManager::addLostMessage(void)
//{
//    m_lostMessages++;
//    emit messageLost(m_lostMessages);
//}

//void SerialPortManager::addSentMessage(void)
//{
//    m_sentMessages++;
//    emit messageSent(m_sentMessages);
//}

//void SerialPortManager::addReceivedMessage(void)
//{
//    m_receivedMessages++;
//    emit messageReceived(m_receivedMessages);
//}

bool SerialPortManager::openPort()
{
    if (m_serialPort.open(QIODevice::ReadWrite))
    {
       emit portOpened();
       return true;
    }
    else
    {
        emit portClosed();
        return false;
    }
}

void SerialPortManager::closePort()
{
    m_serialPort.close();
    emit portClosed();
}

bool SerialPortManager::isOpen()
{
    return m_serialPort.isOpen();
}

void SerialPortManager::handleBytesWritten(qint64 bytes)
{
    m_bytesWritten += bytes;
    if (m_bytesWritten == m_writeData.size())
    {
        m_bytesWritten = 0;
        //qDebug() << "Data successfully sent to port";
    }
}

void SerialPortManager::handleReadyRead()
{
    //aca hay que ir leyendo los bytes y metiendolso en algún lado, cuando se termine un comando, fabricar la acción
    QByteArray bufferAux;
    //qDebug() << "SerialPortManager::handleReadyRead() > bufferAux = " << bufferAux.toHex();
    // FIXME: descartar los 7D e invertir el que sigue a medida que voy recibiendo
    bufferAux = m_serialPort.readAll();
    //qDebug() << "SerialPortManager::handleReadyRead() > bufferAux (2) = " << bufferAux.toHex();

    for (int i = 0; i < bufferAux.size(); i++)
    {
        m_timerR.start(500);

        uint8_t byte = bufferAux[i];

        if (byte == 0x7E)
        {
            findPackets();
        }

        if (m_name == "EAV")
        {
//            qDebug() << hex << byte;
        }
        m_readData.append(byte);
    }

    //qDebug() << "end SerialPortManager::handleReadyRead";
}

void SerialPortManager::setSerialPortName(const QString &serialPortName)
{
    m_serialPort.setPortName(serialPortName);
}

QString SerialPortManager::getSerialPortName(void) const
{
    return m_serialPort.portName();
}

void SerialPortManager::findPackets()
{
    int dataSize = m_readData.size();
    //    //qDebug() << "dataSize = " << dataSize;

    //qDebug() << "findPackets m_readData = " << m_readData.toHex();

    QByteArray aux;
    bool initFlag = false;
    for (int i = 0; i < dataSize; i++)
    {
//        //qDebug() << "i = " << i;

        quint8 value = m_readData.at(i);
//        //qDebug() << "value = " << value;

        if (value == PROTOCOL_INIT_FLAG)
        {
//            //qDebug() << "initFlag = true";

            initFlag = true;
        }
        if ((PROTOCOL_END_FLAG == value) && (i == dataSize-1))
        {
            //mandar señal con paquete nuevo
            if (true == initFlag)
            {
//                //qDebug() << "aux.append( <<" << value <<")";

                aux.append(value);
            }
            emit newPacket(aux);
            emit messageReceived();
//            if (m_name == "EAV") qDebug() << "emit newPacket1: " << aux.toHex();
            aux.clear();
            initFlag = false;
        }
        else if ((PROTOCOL_END_FLAG == value) && (i < dataSize-1) && (PROTOCOL_INIT_FLAG == m_readData.at(i+1)))
        {
            //mandar señal con paquete nuevo
            if (true == initFlag)
            {
//                //qDebug() << "aux.append( <<" << value <<")";

                aux.append(value);
            }
            emit newPacket(aux);
            emit messageReceived();
//            if (m_name == "EAV") qDebug() << "emit newPacket2: " << aux.toHex();
            aux.clear();
            initFlag = false;
        }
        else if ((PROTOCOL_END_FLAG == value) && (i < dataSize-1))
        {
//            //qDebug() << "invertir bit";

            quint8 auxByte = PacketBuilder::invertBit5(m_readData.at(i+1));
            QByteArray aux;
            aux << quint8(auxByte);
            m_readData.replace(i, 2, aux);
            dataSize = m_readData.size();
            value = m_readData.at(i);
        }

        if (true == initFlag)
        {
//            //qDebug() << "aux.append(" << value << ")";

            aux.append(value);
        }


    }
    m_readData.clear();
}


void SerialPortManager::handleTimeoutW()
{
    //qDebug() << "Operation timed out for port";
}

void SerialPortManager::handleTimeoutR()
{
    if (!m_readData.isEmpty())
    {
        findPackets();
    }
}


void SerialPortManager::handleError(QSerialPort::SerialPortError serialPortError)
{
    if (serialPortError == QSerialPort::WriteError)
    {
        //qDebug() << "An I/O error occurred while writing the data to port";
    }
    else if (serialPortError == QSerialPort::ReadError) {
        //qDebug() << "An I/O error occurred while reading the data from port";
    }
}

void SerialPortManager::write(QByteArray &writeData)
{
    if (writeData.isEmpty()) {
        return;
    }

    quint8 command = writeData.at(3);

    m_writeData = PacketBuilder::addEscapeSequences(writeData);
    //qDebug() << "SerialPortManager::write(" << m_writeData.toHex() << ")";
    const qint64 bytesWritten = m_serialPort.write(m_writeData);

    if (bytesWritten == -1)
    {
        //addLostMessage();
        emit messageLost();
        //qDebug() << "Failed to write the data to port";
    }
    else if (bytesWritten != m_writeData.size())
    {
        //addLostMessage();
        emit messageLost();
        //qDebug() << "Failed to write all the data to port";
    }
    else
    {
        emit messageSent();
        //qDebug() << bytesWritten << " bytes wrote successfully";
        emit packetSent(command, m_writeData);
    }

    m_timerW.start(5000);
}
