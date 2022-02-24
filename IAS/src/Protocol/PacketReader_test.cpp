#include "PacketReader.h"
#include "PacketBuilder.h"
#include "KeepaliveCommandReq.h"
#include "ImageHQCommandReq.h"
#include "ImageHQCommandRes.h"
#include "Operators.h"

#include <cstdlib>

#include "gtest/gtest.h"
//#include <QSignalSpy>
#include <KeepaliveCommandRes.h>
#include <QObject>
#include <QDebug>
#include <sstream>

class PacketReaderTest : public testing::Test, public QObject
{
public:
    PacketReaderTest()
    {
        m_byteArray.append(0xFF);
        m_byteArray.append(0xFE);
        m_byteArray.append(0xFD);
        m_byteArray.append(0xFC);
        //4.294.901.244
        m_byteArray.append(0xFB);
        m_byteArray.append(0xFA);
        m_byteArray.append(0xF9);
        m_byteArray.append(0xF8);
        //4.227.529.208
        m_packetReader = new PacketReader(m_byteArray);
    }

protected:
    //Class Under Test
    PacketReader* m_packetReader;
    // Dependencias
    QByteArray m_byteArray;
};

TEST_F(PacketReaderTest, readUChar)
{
    quint8 byte1;
    quint8 byte2;
    quint8 byte3;
    quint8 byte4;
    byte1 = m_packetReader->readUChar();
    byte2 = m_packetReader->readUChar();
    byte3 = m_packetReader->readUChar();
    byte4 = m_packetReader->readUChar();
    ASSERT_EQ(byte1, 0xFF);
    ASSERT_EQ(byte2, 0xFE);
    ASSERT_EQ(byte3, 0xFD);
    ASSERT_EQ(byte4, 0xFC);
}


TEST_F(PacketReaderTest, readUInt32)
{
    quint32 uint1;
    quint32 uint2;
    uint1 = m_packetReader->readUInt32();
    uint2 = m_packetReader->readUInt32();
    ASSERT_EQ(uint1, 4294901244);
    ASSERT_EQ(uint2, 4227529208);
}

TEST_F(PacketReaderTest, skipUInt32)
{
    quint32 uint1;
    m_packetReader->skip(4);
    uint1 = m_packetReader->readUInt32();
    ASSERT_EQ(uint1, 4227529208);
}

TEST_F(PacketReaderTest, getPayload)
{
    PacketBuilder packetFactory;
    QByteArray auxArray;
    QByteArray auxArray2;
    unsigned short fafa = 64250;
    QByteArray keepAlivePacket = packetFactory.createPacket(new KeepaliveCommandReq());
    PacketReader *packetReader = new PacketReader(keepAlivePacket);
    ASSERT_EQ(0, packetReader->payloadSize());
    ASSERT_EQ(0, packetReader->getPayload().size());
    delete(packetReader);
    QByteArray getImageRequestPacket = packetFactory.createPacket(new ImageHQCommandReq(fafa));
    packetReader = new PacketReader(getImageRequestPacket);
    ASSERT_EQ(2, packetReader->payloadSize());
    auxArray << quint16(fafa);
    ASSERT_EQ(auxArray, packetReader->getPayload());
    delete(packetReader);
}

