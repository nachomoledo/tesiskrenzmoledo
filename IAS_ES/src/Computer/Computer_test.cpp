#include "Computer.h"
#include "gtest/gtest.h"

class ComputerAux : public Computer
{
public:
    ComputerAux(QString name) : Computer(name)
    {
        setActionFactory(new ActionFactory());
        setActionManager(new ActionManager());
        setCommManager(new CommManager(nullptr, nullptr, nullptr));
        setTransmissionQueue(new TransmissionQueue());
    }
};

class ComputerTest : public testing::Test
{
public:
    ComputerTest()
    {
        m_computer =  new ComputerAux("");
    }

protected:
    //Class Under Test
    ComputerAux* m_computer;
    // Dependencias
};

TEST_F(ComputerTest, functionTest)
{
    m_computer->setSerialPortName(PortId::ES_IAS_PORT, "");
    m_computer->openPort(PortId::ES_IAS_PORT);
    m_computer->isOpen(PortId::ES_IAS_PORT);
    m_computer->closePort(PortId::ES_IAS_PORT);
    m_computer->isOpen(PortId::ES_IAS_PORT);
    m_computer->name();
    m_computer->getCommManager();
}
