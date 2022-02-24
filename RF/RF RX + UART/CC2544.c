/* RF settings SoC: CC2544 */
PRF_CHAN           = 0x15; // 
PRF_TASK_CONF      = 0x01; // configuration of task control
PRF_CRC_LEN        = 0x02; // crc length.
PRF_CRC_INIT_2     = 0xFF; // initialization value for crc.
PRF_CRC_INIT_3     = 0xFF; // initialization value for crc.
PRF_ADDR_ENTRY_0_0 = 0x01; // address entry 0, index 0. basic mode: conf. see us..
PRF_ADDR_ENTRY_0_1 = 0x40; // address entry 0, index 1. basic mode: rxlength
FRMCTRL0           = 0x41; // 
TXPOWER            = 0xC5; // output power control
LLESTAT            = 0x04; // lle status
MDMCTRL0           = 0x4C; // modem configuration
MDMCTRL1           = 0x48; // modem configuration
MDMCTRL2           = 0x40; // modem configuration
MDMCTRL3           = 0x63; // modem configuration
SW0                = 0x29; // primary sync word byte 0
SW1                = 0x41; // primary sync word byte 1
SW2                = 0x76; // primary sync word byte 2
SW3                = 0x71; // primary sync word byte 3
RXCTRL             = 0x3F; // receive section tuning
FSCTRL             = 0x5A; // frequency synthesizer tuning
ADCTEST0           = 0x66; // 
MDMTEST1           = 0x25; // modem configuration
LLECTRL            = 0x01; // lle control
TXFILTCFG          = 0x07; // tx filter configuration
BSP_P1             = 0x00; // crc polynomial byte 1
BSP_P2             = 0x21; // crc polynomial byte 2
BSP_P3             = 0x10; // crc polynomial byte 3
BSP_MODE           = 0x00; // bit stream processor configuration