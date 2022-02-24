#include "PacketValidator.h"
#include "gtest/gtest.h"


class PacketValidatorTest : public testing::Test
{
public:
    PacketValidatorTest()
    {
    }

protected:
    //Class Under Test
//    PacketValidator* m_packetValidator;
    // Dependencias

};

TEST_F(PacketValidatorTest, functionTest)
{
    PacketValidator::isPacketValid("000000000090e7668a1f560000f056f6b8fe7f000064aea4891f560000010000000000000004000000020000009058f6b8fe7f0000a0e7668a1f560000f056f6b8fe7f0000001f11b9c510d02a6e0000005b00000090e7668a1f5600002057f6b8fe7f00009d63a4891f5600009058f6b8fe7f0000a0e7668a1f560000000000000000000020e7668a1f5600004057f6b8fe7f0000deb7a4891f5600006058f6b8fe7f000008");
//    PacketValidator::isPacketValid({});
}
