/* RF settings SoC: CC2544 */
PRF_CHAN       = 0x29; // 
PRF_TASK_CONF  = 0x01; // configuration of task control
PRF_PKT_CONF   = 0x06; // packet configuration
PRF_CRC_LEN    = 0x02; // crc length.
PRF_CRC_INIT_2 = 0xFF; // initialization value for crc.
PRF_CRC_INIT_3 = 0xFF; // initialization value for crc.
FRMCTRL0       = 0x41; // 
FREQCTRL       = 0x2A; // 
TXPOWER        = 0xE5; // output power control
TXCTRL         = 0x79; // tx settings
LLESTAT        = 0x04; // lle status
MDMCTRL0       = 0x46; // modem configuration
MDMCTRL1       = 0x48; // modem configuration
MDMCTRL2       = 0x40; // modem configuration
MDMCTRL3       = 0x63; // modem configuration
SW0            = 0x29; // primary sync word byte 0
SW1            = 0x41; // primary sync word byte 1
SW2            = 0x76; // primary sync word byte 2
SW3            = 0x71; // primary sync word byte 3
FSCTRL         = 0x75; // frequency synthesizer tuning
LNAGAIN        = 0x00; // lna gain setting
ADCTEST0       = 0x66; // 
MDMTEST0       = 0x01; // modem configuration
MDMTEST1       = 0x25; // modem configuration
LLECTRL        = 0x01; // lle control
ACOMPQS        = 0x16; // quadrature skew setting
TXFILTCFG      = 0x07; // tx filter configuration
BSP_P1         = 0x00; // crc polynomial byte 1
BSP_P2         = 0x21; // crc polynomial byte 2
BSP_P3         = 0x10; // crc polynomial byte 3
BSP_MODE       = 0x00; // bit stream processor configuration
