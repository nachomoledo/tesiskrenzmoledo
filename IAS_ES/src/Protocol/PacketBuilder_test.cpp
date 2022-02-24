#include "PacketBuilder.h"
#include "PacketReader.h"

#include "gtest/gtest.h"
//#include <QSignalSpy>
#include <KeepaliveCommandRes.h>
#include <QDataStream>
#include <QObject>

class PacketBuilderTest : public testing::Test, public QObject
{
public:
    PacketBuilderTest()
    {
        m_packetFactory = new PacketBuilder();
    }

protected:
    //Class Under Test
    PacketBuilder* m_packetFactory;
};

TEST_F(PacketBuilderTest, createKeepaliveMessage)
{
//    QByteArray packetCreated = m_packetFactory->createPacket(static_cast<Command*>(new KeepaliveCommand()));
//    QByteArray packetExpected;
//    packetExpected.append(0x7E); //U8 SYNC
//    packetExpected.append(char(0x00)); //U8 ID
//    packetExpected.append(char(CommandCode::KEEPALIVE)); //U8 CMD
//    packetExpected.append(char(0x00)); //U8 ID
//    packetExpected.append(char(0x00)); //U16 CRC
//    packetExpected.append(char(0x7D)); //U 8 END
//    ASSERT_EQ(packetCreated, packetExpected);

}

TEST_F(PacketBuilderTest, invertBit5)
{
    quint8 aux = 0x7E;
    EXPECT_EQ(m_packetFactory->invertBit5(aux), 0x5E);
    quint8 aux2 = 0x7D;
    EXPECT_EQ(m_packetFactory->invertBit5(aux2), 0x5D);
}

TEST_F(PacketBuilderTest, encodeReservedValue)
{
    quint16 aux;
    QByteArray array;
    array.append((char)0x7D);
    array.append((char)0x5E);
    PacketReader packetReader(array);
    aux = packetReader.readUInt16();
    EXPECT_EQ(m_packetFactory->encodeReservedValue(0x7E), aux);
    quint16 aux2;
    QByteArray array2;
    array2.append((char)0x7D);
    array2.append((char)0x5D);
    PacketReader packetReader2(array2);
    aux2 = packetReader2.readUInt16();
    EXPECT_EQ(m_packetFactory->encodeReservedValue(0x7D), aux2);
}

TEST_F(PacketBuilderTest, addEscapeSequences)
{
    QByteArray aux;
    aux.append(0xFA);
    aux.append(0xFA);
    aux.append(0x7E);
    aux.append(0xFA);
    aux.append(0xFA);
    aux = m_packetFactory->addEscapeSequences(aux);
    EXPECT_EQ(aux.size(), 6);
    EXPECT_EQ(aux.at(0), (char)0xFA);
    EXPECT_EQ(aux.at(1), (char)0xFA);
    EXPECT_EQ(aux.at(2), 0x7D);
    EXPECT_EQ(aux.at(3), 0x5E);
    EXPECT_EQ(aux.at(4), (char)0xFA);
    EXPECT_EQ(aux.at(5), (char)0xFA);
}

TEST_F(PacketBuilderTest, removeEscapeSequences)
{
    QByteArray aux;
    aux.append(0xFA);
    aux.append(0xFA);
    aux.append(0x7D);
    aux.append(0x5E);
    aux.append(0xFA);
    aux.append(0xFA);
    aux = m_packetFactory->removeEscapeSequences(aux);
    EXPECT_EQ(aux.size(), 5);
    EXPECT_EQ(aux.at(0), (char)0xFA);
    EXPECT_EQ(aux.at(1), (char)0xFA);
    EXPECT_EQ(aux.at(2), 0x7E);
    EXPECT_EQ(aux.at(3), (char)0xFA);
    EXPECT_EQ(aux.at(4), (char)0xFA);
}
