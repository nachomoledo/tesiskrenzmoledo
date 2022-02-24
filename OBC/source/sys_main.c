/** @file sys_main.c 
*   @brief Application main file
*   @date 11-Dec-2018
*   @version 04.07.01
*
*   This file contains an empty main function,
*   which can be used for the application.
*/

/* 
* Copyright (C) 2009-2018 Texas Instruments Incorporated - www.ti.com 
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
*    documentation and/or other materials provided with the   
*    distribution.
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
*/


/* USER CODE BEGIN (0) */
/* DEFINES */
//#define FORWARDING_TEST
#define TIMER_PERIOD 125
#define MAX_PAYLOAD_SIZE 255
#define MAX_COMMAND_SIZE 550
#define sbiSTREAM_BUFFER_LENGTH_BYTES        ( ( size_t ) 1024 )
#define sbiSTREAM_BUFFER_TRIGGER_LEVEL_1    ( ( BaseType_t ) 1 )
#define MAX_DEBUG_ARRAY 1024
#define USE_DEBUG_ARRAY 0

/* USER CODE END */

/* Include Files */

#include "sys_common.h"

/* USER CODE BEGIN (1) */
#include "FreeRTOS.h"
#include "sci.h"
#include "os_task.h"
#include "os_timer.h"
#include "os_queue.h"
#include "os_semphr.h"
#include "stream_buffer.h"
#include "het.h"
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
/* ENUMS */
enum CommandId
{
    LED_OBC_GET_REQ = 0x70,
    LED_OBC_GET_RES = 0x71,
    LED_OBC_SET_REQ = 0x72
} CommandId_t;

/* TIPOS */
/* Callback para procesar el comando */
//typedef BaseType_t (*ActionBuilder)(const char *command, size_t commandLen);

/* VARIABLES*/
/* Almacena último byte recibido */
static unsigned char byte;
static unsigned char byte2;
#ifdef FORWARDING_TEST
/* Almacena el comando que se está recibiendo */
static unsigned char command[MAX_COMMAND_SIZE] = {0};
/* Imprime comando */
static void printCommand(unsigned char *buffer, uint32_t length);
#endif
/* Timer para procesar el último comando */
static xTimerHandle timer;
/* Variable para forzar procesar comando */
static bool processCommand = false;
static void forceProcessCommand();
SemaphoreHandle_t xSemaphore;

/* FUNCIONES */
/* Declara tarea para recibir byte */
static void prvTaskRecibirByte(void *pvParameters);

/* LEDS */
/* Port bits connected to LEDs. */
const unsigned long ulLEDBits[] = { 25, 18, 29,     /* Bottom row. */
                                    17, 31, 0,      /* Top row. */
                                    2, 5, 20,       /* Red1, blue1, green1 */
                                    4, 27, 16 };    /* Red2, blue2, green2 */
/* 1 turns a white LED on, or a coloured LED off. */
const unsigned long ulOnStates[] = { 1, 1, 1,
                                     1, 1, 1,
                                     0, 0, 0,
                                     0, 0, 0 };
const unsigned long ulNumLEDs = sizeof( ulLEDBits ) / sizeof( unsigned long );
void initLeds(void);
void gioSetDirection(gioPORT_t *port, unsigned dir);
void gioSetBit(gioPORT_t *port, unsigned bit, unsigned value);
unsigned gioGetBit(gioPORT_t *port, unsigned bit);
void setLed(unsigned long ulLED, unsigned long state);

static QueueHandle_t xQueueUart;

#if USE_DEBUG_ARRAY
uint32_t debugArray[MAX_DEBUG_ARRAY];
int debugArrayIndex = 0;
TickType_t start, end;
#endif

/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */
    /* Enable IRQ interrupts*/
    _enable_IRQ();

    /* Initialize SCI module */
    sciInit();

    initLeds();

#ifdef FORWARDING_TEST
    unsigned char initMessage[] = "Please press a key!\n";
    sciSend(scilinREG, sizeof(initMessage), initMessage);
    sciSend(sciREG, sizeof(initMessage), initMessage);
    sciReceive(scilinREG, 1, (unsigned char *) &command);
    sciReceive(sciREG, 1, (unsigned char *) &command);
    while(1);
#else
    xSemaphore = xSemaphoreCreateMutex();

    xQueueUart = xQueueCreate(512, sizeof(char));

    /* Crear tarea para esperar información por UART */
    xTaskCreate(prvTaskRecibirByte, (const char *)"Recibir byte", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);

    timer = xTimerCreate(
          "timer100ms", /* name */
          pdMS_TO_TICKS(TIMER_PERIOD), /* period/time */
          pdFALSE, /* auto reload */
          (void*)0, /* timer ID */
          forceProcessCommand); /* callback */
    if (NULL == timer)
    {
      for(;;); /* failure! */
    }

    sciReceive(sciREG, 1, &byte);
    sciReceive(scilinREG, 1, &byte2);

    /* Start the tasks and timer running. */
    vTaskStartScheduler();
#endif

/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */
/* Handler de interrupción */
void sciNotification(sciBASE_t *sci, unsigned flags)
{
#ifdef FORWARDING_TEST
    if (sci == scilinREG)
    {
        sciSend(sci, 1, (unsigned char *) &command);
        sciReceive(sci, 1, (unsigned char *) &command);
    }
    else if (sci == sciREG)
    {
        sciSend(sci, 1, (unsigned char *) &command);
        sciReceive(sci, 1, (unsigned char *) &command);
    }
#else
    /* Esta interrupción libera el semáforo para notificar que llegó un byte */
    if (sci == sciREG)
    {
#if USE_DEBUG_ARRAY
        end = xTaskGetTickCountFromISR();
        if (debugArrayIndex < MAX_DEBUG_ARRAY)
        {
            debugArray[debugArrayIndex++] = (end-start)*portTICK_RATE_MS;
        }
#endif
        BaseType_t ret = xQueueSendFromISR(xQueueUart, &byte, NULL);
#if USE_DEBUG_ARRAY
        start = xTaskGetTickCountFromISR();
#endif
        /* Espera el próximo byte */
        sciReceive(sciREG, 1, &byte);
    }
    else if (sci == scilinREG)
    {
        sciSend(sciREG, 1, &byte2);
        sciReceive(scilinREG, 1, &byte2);
    }
#endif

}

/* Error Signal Module (ESM) interrupt notification (Not used but must bue provided) */
void esmGroup1Notification(int bit)
{
    return;
}

/* Error Signal Module (ESM) interrupt notification (Not used but must bue provided) */
void esmGroup2Notification(int bit)
{
    return;
}



#define ARRAY_SIZE 120
uint8_t cRxBuffer[ARRAY_SIZE];
uint32_t xNextByte = 0;
/* Tarea que espera un byte (el semáforo se habilita cuando llega) y lo guarda */
static void prvTaskRecibirByte(void *pvParameters)
{
    uint8_t aux;

    /* Remove warning about unused parameters. */
    ( void ) pvParameters;

    for (;;)
    {
        if ((xQueueReceive(xQueueUart, &aux, portMAX_DELAY ) == pdTRUE))
        {
            if( xSemaphoreTake( xSemaphore, portMAX_DELAY ) == pdTRUE )
            {
                if ((aux == 0x7E) || ((size_t) (xNextByte+1) > ARRAY_SIZE))
                {
                    if (xNextByte > 0)
                    {
                        if (xNextByte > 3)
                        {
                            uint8_t commandId = cRxBuffer[3];

                            if ((commandId != LED_OBC_GET_REQ) && (commandId != LED_OBC_SET_REQ))
                            {
                                    sciSend(scilinREG, xNextByte, cRxBuffer);
                            }
                            else if (commandId == LED_OBC_GET_REQ)
                            {
                                uint8_t buffer[8] = {0x7E, 0x00, 0x00, LED_OBC_GET_RES, 0x01, (uint8_t) gioGetBit(hetPORT, ulLEDBits[0]), 0x00, 0x7D};
                                sciSend(sciREG, 8, buffer);
                            }
                            else
                            {
                                if (xNextByte > 5)
                                {
                                    setLed(0, cRxBuffer[5]);
                                }
                            }
                        }

                        xNextByte = 0;
                    }
                }

                cRxBuffer[xNextByte] = aux;
                xNextByte++;

                if (xTimerReset(timer, 0) != pdPASS)
                {
                  for(;;); /* failure?!? */
                }

                xSemaphoreGive( xSemaphore );
            }
        }
    }
}

static void forceProcessCommand()
{
    if( xSemaphoreTake( xSemaphore, portMAX_DELAY ) == pdTRUE )
    {
        if (xNextByte > 0)
        {
            if (xNextByte > 3)
            {
                uint8_t commandId = cRxBuffer[3];

                if ((commandId != LED_OBC_GET_REQ) && (commandId != LED_OBC_SET_REQ))
                {
                        sciSend(scilinREG, xNextByte, cRxBuffer);
                }
                else if (commandId == LED_OBC_GET_REQ)
                {
                    uint8_t buffer[8] = {0x7E, 0x00, 0x00, LED_OBC_GET_RES, 0x01, (uint8_t) gioGetBit(hetPORT, ulLEDBits[0]), 0x00, 0x7D};
                    sciSend(sciREG, 8, buffer);
                }
                else
                {
                    if (xNextByte > 5)
                    {
                        setLed(0, cRxBuffer[5]);
                    }
                }
            }

            xNextByte = 0;
        }
    xSemaphoreGive( xSemaphore );
    }
}

#ifdef FORWARDING_TEST
void printCommand(unsigned char *buffer, uint32_t length)
{
    unsigned char mensaje[] = "\nComando: ";
    sciSend(sciREG, sizeof(mensaje), mensaje);
    sciSend(sciREG, length, buffer);
    sciSend(sciREG, 1, "\n");
}
#endif

void initLeds( void )
{
unsigned long ul;

    /* Initalise the IO ports that drive the LEDs */
    gioSetDirection( hetPORT, 0xFFFFFFFF );

    /* Turn all the LEDs off. */
    for( ul = 0; ul < ulNumLEDs; ul++ )
    {
        gioSetBit( hetPORT, ulLEDBits[ ul ], !ulOnStates[ ul ] );
    }
}

/** @fn void gioSetDirection(gioPORT_t *port, unsigned dir)
*   @brief Set Port Direction
*   @param[in] port pointer to GIO port:
*              - gioPORTA: PortA pointer
*              - gioPORTB: PortB pointer
*   @param[in] dir value to write to DIR register
*
*   Set the direction of GIO pins at runtime.
*/
void gioSetDirection(gioPORT_t *port, unsigned dir)
{
    port->DIR = dir;
}

/** @fn void gioSetBit(gioPORT_t *port, unsigned bit, unsigned value)
*   @brief Write Bit
*   @param[in] port pointer to GIO port:
*              - gioPORTA: PortA pointer
*              - gioPORTB: PortB pointer
*   @param[in] bit number 0-7 that specifies the bit to be written to.
*              - 0: LSB
*              - 7: MSB
*   @param[in] value binrary value to write to bit
*
*   Writes a value to the specified pin of the given GIO port
*/
void gioSetBit(gioPORT_t *port, unsigned bit, unsigned value)
{
    if (value)
    {
        port->DSET = 1 << bit;
    }
    else
    {
        port->DCLR = 1 << bit;
    }
}

void setLed(unsigned long ulLED, unsigned long state)
{
    if( ulLED < ulNumLEDs )
    {
        gioSetBit(hetPORT, ulLEDBits[ulLED], state);
    }
}

/** @fn unsigned gioGetBit(gioPORT_t *port, unsigned bit)
*   @brief Read Bit
*   @param[in] port pointer to GIO port:
*              - gioPORTA: PortA pointer
*              - gioPORTB: PortB pointer
*   @param[in] bit number 0-7 that specifies the bit to be written to.
*              - 0: LSB
*              - 7: MSB
*
*   Reads a the current value from the specified pin of the given GIO port
*/
unsigned gioGetBit(gioPORT_t *port, unsigned bit)
{
    return (port->DIN >> bit) & 1U;
}
/* USER CODE END */
