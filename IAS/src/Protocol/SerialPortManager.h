#ifndef SERIALPORTMANAGER_H
#define SERIALPORTMANAGER_H

#include <QObject>
#include <QSerialPort>
#include <QStringList>
#include <QTimer>

#define DEFAULT_BAUDRATE QSerialPort::Baud115200

class SerialPortManager : public QObject
{
    Q_OBJECT
    //una queue con comandos
private:
    QString m_name;
    QSerialPort m_serialPort;
    QByteArray m_writeData;
    qint64 m_bytesWritten;
    QTimer m_timerW;
    QByteArray m_readData;
    QTimer m_timerR;
//    quint32 m_lostMessages;
//    quint32 m_sentMessages;
//    quint32 m_receivedMessages;
    void findPackets(void);
//    void addLostMessage(void);
//    void addSentMessage(void);
//    void addReceivedMessage(void);
public:
    SerialPortManager(QString name = "", const int &baudRate = DEFAULT_BAUDRATE, QObject *parent = nullptr);
    void write(QByteArray &writeData);

    bool openPort();
    void closePort();
    void setSerialPortName(const QString &serialPortName);
    QString getSerialPortName(void) const;
    bool isOpen();

public slots:
    void handleBytesWritten(qint64 bytes);
    void handleReadyRead();
    void handleTimeoutW();
    void handleTimeoutR();
    void handleError(QSerialPort::SerialPortError error);

signals:
    void newPacket(QByteArray &packet);
    void portOpened();
    void portClosed();
    void messageLost(/*quint32 total*/);
    void messageSent(/*quint32 total*/);
    void messageReceived(/*quint32 total*/);
    void packetSent(quint8 commandCode, QByteArray packet);

};

#endif // SERIALPORTMANAGER_H
