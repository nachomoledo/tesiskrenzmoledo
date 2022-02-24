/*******************************************************************************
*  Filename:        clock.h
*  Revised:         $Date: 2013-04-19 17:03:45 +0200 (fr, 19 apr 2013) $
*  Revision:        $Revision: 9891 $
*
*  Description:     This file defines clock related functions for the CC254x 
*                   family of RF system-on-chips from Texas Instruments.
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

#ifndef _CLOCK_H
#define _CLOCK_H
/*******************************************************************************
 * INCLUDES
 */
#include <hal_types.h>
#include <hal_defs.h>
// Include chip specific IO definition file
#if (chip == 2541)
#include <ioCC2541.h>
#endif
#if (chip == 2543)
#include <ioCC2543.h>
#endif
#if (chip == 2544)
#include <ioCC2544.h>
#endif
#if (chip == 2545)
#include <ioCC2545.h>
#endif


/*******************************************************************************
 * CONSTANTS
 */

/* SEE USER GUIDE FOR DETAILS ABOUT THE FOLLOWING BIT MASKS */

// Parameters for cc254X System clock-source select.
#define CLOCK_SRC_XOSC      0  // High speed Crystal Oscillator Control.
#define CLOCK_SRC_HFRC      1  // Low power RC Oscillator.

// for CC2541/5 external 32KHz crystal.
#define CLOCK_32K_XTAL      0  // 32.768 Hz crystal oscillator.
#define CLOCK_32K_RCOSC     1  // 32 kHz RC oscillator.

// Bit masks to check CLKCON register.
#define CLKCON_OSC32K_BM    0x80  // bit mask, for the slow 32k clock oscillator.
#define CLKCON_OSC_BM       0x40  // bit mask, for the system clock oscillator.
#define CLKCON_TICKSPD_BM   0x38  // bit mask, for timer ticks output setting.
#define CLKCON_CLKSPD_BM    0x07  // bit maks, for the clock speed. 

#define TICKSPD_DIV_1       (0x00 << 3)
#define TICKSPD_DIV_2       (0x01 << 3)
#define TICKSPD_DIV_4       (0x02 << 3)
#define TICKSPD_DIV_8       (0x03 << 3)
#define TICKSPD_DIV_16      (0x04 << 3)
#define TICKSPD_DIV_32      (0x05 << 3)
#define TICKSPD_DIV_64      (0x06 << 3)
#define TICKSPD_DIV_128     (0x07 << 3)

// Bit masks to check SLEEPSTA register.
#define SLEEP_XOSC_STB_BM   0x40  // bit mask, check the stability of XOSC.
#define SLEEP_HFRC_STB_BM   0x20  // bit maks, check the stability of the High-frequency RC oscillator.
#define SLEEP_OSC_PD_BM     0x04  // bit mask, power down system clock oscillator(s).


/*******************************************************************************
 * MACROS
 */

// Macro for checking status of the high frequency RC oscillator.
#define CC254x_IS_HFRC_STABLE(x)    (SLEEPSTA & SLEEP_HFRC_STB_BM)

// Macro for checking status of the crystal oscillator
#define CC254x_IS_XOSC_STABLE(x)    (SLEEPSTA & SLEEP_XOSC_STB_BM)

// Macro for getting the clock division factor
#define CC254x_GET_CLKSPD(x)        (CLKCONSTA & CLKCON_CLKSPD_BM)

// Macro for getting the timer tick division factor.
#define CC254x_GET_TICKSPD(x)       ((CLKCONSTA & CLKCON_TICKSPD_BM) >> 3)

// Macro for setting the timer tick division factor, x value from 0b000 to 0b111
#define CC254x_SET_TICKSPD(x)        st( CLKCONCMD = ((((x) << 3) & 0x38)  \
                                                    | (CLKCONCMD & 0xC7)); \		                                                              )

// Macro for setting the clock division factor, x value from 0b000 to 0b111
#define CC254x_SET_CLKSPD(x)         st( CLKCONCMD = (((x) & 0x07)         \
                                                    | (CLKCONCMD & 0xF8)); \
							                      )

// Macro for waiting for clock updates
#define CC254x_WAIT_CLK_UPDATE()    st( uint8 ____clkcon; \
                                        uint8 ____clkconsta; \
                                        ____clkcon = CLKCONCMD; \
                                        do { \
                                          ____clkconsta = CLKCONSTA; \
                                        } while (____clkconsta != ____clkcon); )


/*******************************************************************************
 * FUNCTIONS
 */
void clockSetMainSrc(uint8 source);
uint8 clockSelect32k(uint8 source);
uint8 clockSetMainClkSpeed(uint8 clkSpeed);


#endif