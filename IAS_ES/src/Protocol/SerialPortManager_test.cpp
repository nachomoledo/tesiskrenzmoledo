#include "SerialPortManager.h"
#include "gtest/gtest.h"


class SerialPortManagerTest : public testing::Test
{
public:
    SerialPortManagerTest()
    {
        m_serialPortManager = new SerialPortManager();
    }

protected:
    //Class Under Test
    SerialPortManager* m_serialPortManager;
    // Dependencias

};

TEST_F(SerialPortManagerTest, functionTest)
{
    QByteArray qba;
    m_serialPortManager->write(qba);
    m_serialPortManager->openPort();
    m_serialPortManager->closePort();
    m_serialPortManager->setSerialPortName("");
    m_serialPortManager->getSerialPortName();
    m_serialPortManager->isOpen();
}
