/*******************************************************************************
*  Filename:        dma.h
*  Revised:         $Date: 2013-04-19 17:03:45 +0200 (fr, 19 apr 2013) $
*  Revision:        $Revision: 9891 $
*
*  Description:     The macros and structs in this section simplify setup and 
*                   usage of DMA. The CC2541 has five DMA channels while the 
*                   CC2543, CC2544 and CC2545 only have two.
*
*
*  Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
*
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*******************************************************************************/

#ifndef _DMA_H_
#define _DMA_H_
/*******************************************************************************
* INCLUDES
*/
#include <hal_types.h>


/*******************************************************************************
* CONSTANTS AND DEFINES
*/
#define DMA_CHANNEL_0                0x01
#define DMA_CHANNEL_1                0x02
#define DMA_CHANNEL_2                0x04
#define DMA_CHANNEL_3                0x08
#define DMA_CHANNEL_4                0x10
#define DMA_VLEN_USE_LEN             0x00 // Use LEN for transfer count
#define DMA_VLEN_FIXED               0x00 // Use LEN for transfer count
#define DMA_VLEN_1_P_VALOFFIRST      0x01 // Transfer the first byte + the number of bytes indicated by the first byte
#define DMA_VLEN_VALOFFIRST          0x02 // Transfer the number of bytes indicated by the first byte (starting with the first byte)
#define DMA_VLEN_1_P_VALOFFIRST_P_1  0x03 // Transfer the first byte + the number of bytes indicated by the first byte + 1 more byte
#define DMA_VLEN_1_P_VALOFFIRST_P_2  0x04 // Transfer the first byte + the number of bytes indicated by the first byte + 2 more bytes
#define DMA_WORDSIZE_BYTE            0x00 // Transfer a byte at a time
#define DMA_WORDSIZE_WORD            0x01 // Transfer a 16-bit word at a time
#define DMA_TMODE_SINGLE             0x00 // Transfer a single byte/word after each DMA trigger
#define DMA_TMODE_BLOCK              0x01 // Transfer block of data (length len) after each DMA trigger
#define DMA_TMODE_SINGLE_REPEATED    0x02 // Transfer single byte/word (after len transfers, rearm DMA)
#define DMA_TMODE_BLOCK_REPEATED     0x03 // Transfer block of data (after len transfers, rearm DMA)

#if (chip == 2544)
    #define DMA_TRIG_NONE                0    // No trigger, setting DMAREQ.DMAREQx bit starts transfer
    #define DMA_TRIG_PREV                1    // DMA channel is triggered by completion of previous channel
    #define DMA_TRIG_T1_CH0              2    // Timer 1, compare, channel 0
    #define DMA_TRIG_T1_CH1              3    // Timer 1, compare, channel 1
    #define DMA_TRIG_T1_CH2              4    // Timer 1, compare, channel 2
    #define DMA_TRIG_T2_EVENT1           5    // Timer 2, event pulse 1
    #define DMA_TRIG_T2_EVENT2           6    // Timer 2, event pulse 2
    #define DMA_TRIG_T3_CH0              7    // Timer 3, compare, channel 0
    #define DMA_TRIG_T3_CH1              8    // Timer 3, compare, channel 1
    #define DMA_TRIG_T4_CH0              9    // Timer 4, compare, channel 0
    #define DMA_TRIG_T4_CH1              10   // Timer 4, compare, channel 1
    #define DMA_TRIG_RADIO1              11   // Radio trigger 1
    #define DMA_TRIG_URX0                14   // USART RX complete
    #define DMA_TRIG_UTX0                15   // USART TX complete
    #define DMA_TRIG_FLASH               18   // Flash data write complete
    #define DMA_TRIG_RADIO               19   // RF packet byte received/transmit
    #define DMA_TRIG_IOC_0_0             20   // I/O controller P0.0 I/O pin transition
    #define DMA_TRIG_IOC_0_1             21   // I/O controller P0.1 I/O pin transition
    #define DMA_TRIG_IOC_0_2             22   // I/O controller P0.2 I/O pin transition
    #define DMA_TRIG_IOC_0_3             23   // I/O controller P0.3 I/O pin transition
    #define DMA_TRIG_IOC_1_0             24   // I/O controller P1.0 I/O pin transition
    #define DMA_TRIG_IOC_1_1             25   // I/O controller P1.1 I/O pin transition
    #define DMA_TRIG_IOC_1_2             26   // I/O controller P1.2 I/O pin transition
    #define DMA_TRIG_IOC_1_3             27   // I/O controller P1.3 I/O pin transition
    #define DMA_TRIG_ST                  28   // Sleep timer compare
    #define DMA_TRIG_ENC_DW              29   // AES encryption processor requests download input data
    #define DMA_TRIG_ENC_UP              30   // AES encryption processor requests upload output data
    #define DMA_TRIG_DBG_BW              31   // Debug interface burst write
#elif (chip == 2543 || chip == 2545)
    #define DMA_TRIG_NONE                0    // No trigger, setting DMAREQ.DMAREQx bit starts transfer
    #define DMA_TRIG_PREV                1    // DMA channel is triggered by completion of previous channel
    #define DMA_TRIG_T1_CH0              2    // Timer 1, compare, channel 0
    #define DMA_TRIG_T1_CH1              3    // Timer 1, compare, channel 1
    #define DMA_TRIG_T1_CH2              4    // Timer 1, compare, channel 2
    #define DMA_TRIG_T2_EVENT1           5    // Timer 2, event pulse 1
    #define DMA_TRIG_T2_EVENT2           6    // Timer 2, event pulse 2
    #define DMA_TRIG_T3_CH0              7    // Timer 3, compare, channel 0
    #define DMA_TRIG_T3_CH1              8    // Timer 3, compare, channel 1
    #define DMA_TRIG_T4_CH0              9    // Timer 4, compare, channel 0
    #define DMA_TRIG_T4_CH1              10   // Timer 4, compare, channel 1
    #define DMA_TRIG_RADIO1              11   // Radio trigger 1
    #define DMA_TRIG_IOC_0               12   // USART 0 Port 0 I/O pin input transition
    #define DMA_TRIG_IOC_1               13   // USART 0 Port 1 I/O pin input transition
    #define DMA_TRIG_URX0                14   // USART0 RX complete
    #define DMA_TRIG_UTX0                15   // USART0 TX complete
    #define DMA_TRIG_ST                  16   // Sleep timer compare
    #define DMA_TRIG_FLASH               18   // Flash data write complete
    #define DMA_TRIG_RADIO               19   // Radio trigger 0
    #define DMA_TRIG_ADC_CHALL           20   // ADC end of a conversion in a sequence, sample ready
    #define DMA_TRIG_ADC_CH0             21   // ADC end of conversion channel 0 in sequence, sample ready
    #define DMA_TRIG_ADC_CH1             22   // ADC end of conversion channel 1 in sequence, sample ready
    #define DMA_TRIG_ADC_CH2             23   // ADC end of conversion channel 2 in sequence, sample ready
    #define DMA_TRIG_ADC_CH3             24   // ADC end of conversion channel 3 in sequence, sample ready
    #define DMA_TRIG_ADC_CH4             25   // ADC end of conversion channel 4 in sequence, sample ready
    #define DMA_TRIG_ADC_CH5             26   // ADC end of conversion channel 5 in sequence, sample ready
    #define DMA_TRIG_ADC_CH6             27   // ADC end of conversion channel 6 in sequence, sample ready
    #define DMA_TRIG_ADC_CH7             28   // ADC end of conversion channel 7 in sequence, sample ready
    #define DMA_TRIG_ENC_DW              29   // AES encryption processor requests download input data
    #define DMA_TRIG_ENC_UP              30   // AES encryption processor requests upload output data
    #define DMA_TRIG_DBG_BW              31   // Debug interface burst write
#elif (chip == 2541)
    #define DMA_TRIG_NONE                0    // No trigger, setting DMAREQ.DMAREQx bit starts transfer
    #define DMA_TRIG_PREV                1    // DMA channel is triggered by completion of previous channel
    #define DMA_TRIG_T1_CH0              2    // Timer 1, compare, channel 0
    #define DMA_TRIG_T1_CH1              3    // Timer 1, compare, channel 1
    #define DMA_TRIG_T1_CH2              4    // Timer 1, compare, channel 2
    #define DMA_TRIG_T2_EVENT1           5    // Timer 2, event pulse 1
    #define DMA_TRIG_T2_EVENT2           6    // Timer 2, event pulse 2
    #define DMA_TRIG_T3_CH0              7    // Timer 3, compare, channel 0
    #define DMA_TRIG_T3_CH1              8    // Timer 3, compare, channel 1
    #define DMA_TRIG_T4_CH0              9    // Timer 4, compare, channel 0
    #define DMA_TRIG_T4_CH1              10   // Timer 4, compare, channel 1
    #define DMA_TRIG_RADIO1              11   // Radio trigger 1
    #define DMA_TRIG_IOC_0               12   // I/O controller Port 0 I/O pin input transition
    #define DMA_TRIG_IOC_1               13   // I/O controller Port 1 I/O pin input transition
    #define DMA_TRIG_URX0                14   // USART 0 RX complete
    #define DMA_TRIG_UTX0                15   // USART 0 TX complete
    #define DMA_TRIG_URX1                16   // USART 1 RX complete
    #define DMA_TRIG_UTX1                17   // USART 1 TX complete
    #define DMA_TRIG_FLASH               18   // Flash data write complete
    #define DMA_TRIG_RADIO               19   // Radio trigger 0
    #define DMA_TRIG_ADC_CHALL           20   // ADC end of a conversion in a sequence, sample ready
    #define DMA_TRIG_ADC_CH0             21   // ADC end of conversion channel 0 in sequence, sample ready
    #define DMA_TRIG_ADC_CH1             22   // ADC end of conversion channel 1 in sequence, sample ready
    #define DMA_TRIG_ADC_CH2             23   // ADC end of conversion channel 2 in sequence, sample ready
    #define DMA_TRIG_ADC_CH3             24   // ADC end of conversion channel 3 in sequence, sample ready
    #define DMA_TRIG_ADC_CH4             25   // ADC end of conversion channel 4 in sequence, sample ready
    #define DMA_TRIG_ADC_CH5             26   // ADC end of conversion channel 5 in sequence, sample ready
    #define DMA_TRIG_ADC_CH6             27   // ADC end of conversion channel 6 in sequence, sample ready
    #define DMA_TRIG_ADC_CH7             28   // ADC end of conversion channel 7 in sequence, sample ready
    #define DMA_TRIG_ENC_DW              29   // AES encryption processor requests download input data
    #define DMA_TRIG_ENC_UP              30   // AES encryption processor requests upload output data
    #define DMA_TRIG_DBG_BW              31   // Debug interface burst write
#endif

#define DMA_SRCINC_0                 0x00 // Increment source pointer by 0 bytes/words after each transfer
#define DMA_SRCINC_1                 0x01 // Increment source pointer by 1 bytes/words after each transfer
#define DMA_SRCINC_2                 0x02 // Increment source pointer by 2 bytes/words after each transfer
#define DMA_SRCINC_M1                0x03 // Decrement source pointer by 1 bytes/words after each transfer
#define DMA_DESTINC_0                0x00 // Increment destination pointer by 0 bytes/words after each transfer
#define DMA_DESTINC_1                0x01 // Increment destination pointer by 1 bytes/words after each transfer
#define DMA_DESTINC_2                0x02 // Increment destination pointer by 2 bytes/words after each transfer
#define DMA_DESTINC_M1               0x03 // Decrement destination pointer by 1 bytes/words after each transfer
#define DMA_IRQMASK_DISABLE          0x00 // Disable interrupt generation
#define DMA_IRQMASK_ENABLE           0x01 // Enable interrupt generation upon DMA channel done
#define DMA_M8_USE_8_BITS            0x00 // Use all 8 bits for transfer count
#define DMA_M8_USE_7_BITS            0x01 // Use 7 LSB for transfer count
#define DMA_PRI_LOW                  0x00 // Low, CPU has priority
#define DMA_PRI_GUARANTEED           0x01 // Guaranteed, DMA at least every second try
#define DMA_PRI_HIGH                 0x02 // High, DMA has priority
#define DMA_PRI_ABSOLUTE             0x03 // Highest, DMA has priority. Reserved for DMA port access.


// Place the bitfield members from the most significant bit to the least significant bit.
#pragma bitfields=reversed
typedef struct {
    uint8 srcAddrH;
    uint8 srcAddrL;
    uint8 destAddrH;
    uint8 destAddrL;
    uint8 vlen      : 3;
    uint8 lenH      : 5;
    uint8 lenL      : 8;
    uint8 wordSize  : 1;
    uint8 tMode     : 2;
    uint8 trig      : 5;
    uint8 srcInc    : 2;
    uint8 destInc   : 2;
    uint8 irqMask   : 1;
    uint8 m8        : 1;
    uint8 priority  : 2;
} DMA_DESC;
#pragma bitfields=default


/*******************************************************************************
 * MACROS
 */

#define DMA_SET_ADDR_DESC0(addr)                st( DMA0CFGH = HI_UINT16(addr); DMA0CFGL = LO_UINT16(addr); )
#define DMA_SET_ADDR_DESC1234(addr)             st( DMA1CFGH = HI_UINT16(addr); DMA1CFGL = LO_UINT16(addr); )
#define DMA_CHANNEL_ARM(channel_bitmask)        st( DMAARM = (channel_bitmask) & 0x1F; )
#define DMA_CHANNEL_TRIG(channel_bitmask)       st( DMAREQ = (channel_bitmask); )
#define DMA_CHANNEL_ABORT(channel_bitmask)      (DMAARM = (0x80 | (channel_bitmask)))
#define DMA_CHANNEL_ACTIVE(channel_bitmask)     (DMAARM & (channel_bitmask))
#define DMA_INT_CLEAR()     (DMAIF = 0)
#define DMA_INT_ENABLE()    (DMAIE = 1)
#define DMA_INT_DISABLE()   (DMAIE = 0)


#endif