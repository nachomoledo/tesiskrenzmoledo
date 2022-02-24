/*******************************************************************************
*  Filename:        hal_joystick.c
*  Revised:         $Date: 2013-04-22 10:49:57 +0200 (ma, 22 apr 2013) $
*  Revision:        $Revision: 9900 $
*
*  Description:     HAL joystick control implementation file
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


/*******************************************************************************
 * INCLUDES
 */
#define xJOYSTICK_ISR

#include <hal_board.h>
#include <adc.h>
#include <hal_joystick.h>

#ifdef JOYSTICK_ISR
#include "hal_int.h"
#include "hal_digio.h"
#endif


/*******************************************************************************
* DEFINTIONs
*/

/*******************************************************************************
* CONSTANTS
*/
#define JOYSTICK_UP_BM              BM(HAL_BOARD_IO_JOY_UP_PIN)
#define JOYSTICK_DOWN_BM            BM(HAL_BOARD_IO_JOY_DN_PIN)
#define JOYSTICK_LEFT_BM            BM(HAL_BOARD_IO_JOY_LT_PIN)
#define JOYSTICK_RIGHT_BM           BM(HAL_BOARD_IO_JOY_RT_PIN)


#define HAL_BOARD_IO_JOYSTICK_ADC_CH    HAL_BOARD_IO_JOYSTICK_ADC_PIN

/*******************************************************************************
* LOCAL VARIABLES
*/
#ifdef JOYSTICK_ISR
static const digioConfig pinJoystickMove = {HAL_BOARD_IO_JOY_MOVE_PORT,
                                            HAL_BOARD_IO_JOY_MOVE_PIN,
                                            BV(HAL_BOARD_IO_JOY_MOVE_PIN),
                                            HAL_DIGIO_INPUT, 0};
static void halJoystickMoveISR(void);
static ISR_FUNC_PTR joystick_isr_tbl[HAL_JOYSTICK_EVT_MAX] = {0};
#endif

/*******************************************************************************
* @fn      halJoystickInit
*
* @brief   Initializes the joystick functionality
*
* @param  void
*
* @return void
*
*/
void halJoystickInit(void) {
    // Joystick push input
    MCU_IO_INPUT(HAL_BOARD_IO_JOY_MOVE_PORT, HAL_BOARD_IO_JOY_MOVE_PIN, \
        MCU_IO_TRISTATE);
    
    // Analog input
    MCU_IO_PERIPHERAL(HAL_BOARD_IO_JOYSTICK_ADC_PORT, HAL_BOARD_IO_JOYSTICK_ADC_PIN);
    
#ifdef JOYSTICK_ISR
    halDigioConfig(&pinJoystickMove);
    halDigioIntSetEdge(&pinJoystickMove, HAL_DIGIO_INT_RISING_EDGE);
    halDigioIntConnect(&pinJoystickMove, &halJoystickMoveISR);
#endif
}

#ifdef JOYSTICK_ISR
/*******************************************************************************
* @fn      halJoystickIntConnect
*
* @brief   Connect isr for joystick move interrupt. The parameter event tells for
*          which joystick direction this isr should be called.
*
* @param   event - Joystick direction
*          func - Pointer to function to connect
*
* @return  none
*/
uint8 halJoystickIntConnect(uint8 event, ISR_FUNC_PTR func) {
    istate_t key;
    HAL_INT_LOCK(key);
    switch(event) {
    case HAL_JOYSTICK_EVT_UP:
        joystick_isr_tbl[HAL_JOYSTICK_EVT_UP] = func;
        break;
    case HAL_JOYSTICK_EVT_DOWN:
        joystick_isr_tbl[HAL_JOYSTICK_EVT_DOWN] = func;
        break;
    case HAL_JOYSTICK_EVT_LEFT:
        joystick_isr_tbl[HAL_JOYSTICK_EVT_LEFT] = func;
        break;
    case HAL_JOYSTICK_EVT_RIGHT:
        joystick_isr_tbl[HAL_JOYSTICK_EVT_RIGHT] = func;
        break;
    case HAL_JOYSTICK_EVT_PUSHED:
        joystick_isr_tbl[HAL_JOYSTICK_EVT_PUSHED] = func;
        break;
    default:
        HAL_INT_UNLOCK(key); return FAILED;
    }
    HAL_INT_UNLOCK(key);
    return SUCCESS;
}

/*******************************************************************************
* @fn      halJoystickIntEnable
*
* @brief   Enable joystick move interrupt
*
* @param   event - Joystick direction
*
* @return  none
*/
uint8 halJoystickIntEnable(uint8 event) {
   // Ignore event parameter
    halDigioIntEnable(&pinJoystickMove);
    return SUCCESS;
}


/*******************************************************************************
* @fn      halJoystickIntDisable
*
* @brief   Disable joystick move interrupt
*
* @param   none
*
* @return  none
*/
void halJoystickIntDisable(void) {
   halDigioIntDisable(&pinJoystickMove);
}

/*******************************************************************************
* @fn      halJoystickIntClear
*
* @brief   Clear pending joystick interrupts
*
* @param   event - Joystick direction
*
* @return  none
*/
void halJoystickIntClear(void) {
    halDigioIntClear(&pinJoystickMove);
}
#endif


/*******************************************************************************
* @fn  halJoystickPushed
*
* @brief
*      This function detects if the joystick is being pushed. The function
*      implements software debounce. Return true only if previuosly called
*      with joystick not pushed. Return true only once each time the joystick
*      is pressed.
*
* Parameters:
*
* @param  void
*
* @return uint8
*          1: Button is being pushed
*          0: Button is not being pushed
*
*/
uint8 halJoystickPushed(void) {
    uint8 value, active, i;
    static uint8 prevValue = 0;
    uint16 adcValue;
    
    // Criterion for button pushed:
    // 3 times joystick active and in center position
    value = 1;
    for (i=0; i<3; i++) {
        active = MCU_IO_GET(HAL_BOARD_IO_JOY_MOVE_PORT, HAL_BOARD_IO_JOY_MOVE_PIN);
        adcValue = adcSampleSingle(ADC_REF_AVDD, ADC_9_BIT, \
          HAL_BOARD_IO_JOYSTICK_ADC_CH);
        // Only use 7 out of the 9 bits
        adcValue = (adcValue & 0x7FC0) >> 8;
        if (! active || adcValue < 0x54) {
            // Joystick not active or not in center position
            value = 0;
            break;
        }
        halMcuWaitUs(3);
    }
    
    if (value){
        if (!prevValue){
            value = prevValue = 1;
            halMcuWaitMs(100);
        }
        else {
            value = 0;
        }
    }
    else{
        prevValue = 0;
    }
    return value;
}

/*******************************************************************************
* @fn  halJoystickGetDir
*
* @brief
*      This function checks the P3.X inpuit pins.
*
*
*       All the joystick directions are connected to pins on port 3
*       JOYSTICK_UP - P3.1
*       JOYSTICK_PUSH - P3.6
*       JOYSTICK_LT - P3.3
*       JOYSTICK_RT - P3.2
*       JOYSTICK_DN - P3.0
*
* Parameters:
*
* @param  void
*
* @return uint8
*          DOWN:    Joystick direction is down    (270 degrees)
*          LEFT:    Joystick direction is left    (180 degrees)
*	   RIGHT:   Joystick direction is right   (0 degrees)
*	   UP:      Joystick direction is up      (90 degrees)
*	   CENTER:  Joystick direction is centred (passive position)
*
*/
uint8 halJoystickGetDir(void) {
    uint8  direction, directionOld;

    do {
        directionOld = direction;

        if (P3_1) {
            direction = HAL_JOYSTICK_EVT_UP;
        } else if (P3_0) {
            direction = HAL_JOYSTICK_EVT_DOWN;
        } else if (P3_3) {
            direction = HAL_JOYSTICK_EVT_LEFT;
        } else if (P3_2) {
            direction = HAL_JOYSTICK_EVT_RIGHT;
        } else {
            direction = HAL_JOYSTICK_EVT_CENTER;
        }

    } while(direction != directionOld);

    return direction;
}

#ifdef JOYSTICK_ISR
/*******************************************************************************
* @fn      halJoystickMoveISR
*
* @brief   Interrupt service routine for joystick move interrupt
*
* @param   none
*
* @return  none
*/
static void halJoystickMoveISR(void) {
    uint8 direction = halJoystickGetDir();

    switch(direction)
    {
    case HAL_JOYSTICK_EVT_DOWN:
      if (joystick_isr_tbl[HAL_JOYSTICK_EVT_DOWN]){
        (*joystick_isr_tbl[HAL_JOYSTICK_EVT_DOWN])();
      }
        break;
    case HAL_JOYSTICK_EVT_LEFT:
      if (joystick_isr_tbl[HAL_JOYSTICK_EVT_LEFT]){
        (*joystick_isr_tbl[HAL_JOYSTICK_EVT_LEFT])();
      }
        break;
    case HAL_JOYSTICK_EVT_RIGHT:
      if (joystick_isr_tbl[HAL_JOYSTICK_EVT_RIGHT]){
        (*joystick_isr_tbl[HAL_JOYSTICK_EVT_RIGHT])();
      }
        break;
    case HAL_JOYSTICK_EVT_UP:
      if (joystick_isr_tbl[HAL_JOYSTICK_EVT_UP]){
        (*joystick_isr_tbl[HAL_JOYSTICK_EVT_UP])();
      }
        break;
    case HAL_JOYSTICK_EVT_CENTER:
      // Interrupt while in center means joystick is pushed
      if (joystick_isr_tbl[HAL_JOYSTICK_EVT_PUSHED]){
        (*joystick_isr_tbl[HAL_JOYSTICK_EVT_PUSHED])();
      }
        break;
    default:
      // no action
      break;
    }
}
#endif