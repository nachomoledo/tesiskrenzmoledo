/* RECEPTOR */

/*******************************************************************************
* INCLUDES
*/

// Definiciones de tipo HAL
#include <hal_types.h> 

// Definiciones de bits individuales de los registros de los dispositivos CC254x
#include <ioCC254x_bitdef.h>

// Incluye archivos especificos de CC2544
#include "ioCC2544.h"

// Funciones HAL
#include "hal_rf_proprietary.h" 
#include "hal_int.h"
#include "hal_timer2.h"

#include "circular_buffer.h"


/*******************************************************************************
* CONSTANTES
*/

// Palabra de sincronizacion (iguales en ambos dispositivos)
#define SYNCWORD 0x29417671

// Con estos valores, se obtiene un baudrate de 2.00 Mbps con un clock de 32 MHz
//#define UART_BAUD_M  0
//#define UART_BAUD_E  16

// Con estos valores, se obtiene un baudrate de 115200 con un clock de 32 MHz
#define UART_BAUD_M  216
#define UART_BAUD_E  11

#define DEBUG_BUFFER_SIZE  255

#define USE_DEBUG_BUFFER 1

/*******************************************************************************
* VARIABLES LOCALES
*/
extern volatile uint8 rfirqf1; // Bandera de interrupcion
#if USE_DEBUG_BUFFER
static uint8 debugArray[DEBUG_BUFFER_SIZE];
#endif
static circular_buffer cb;

/*******************************************************************************
* LOCAL FUNCTIONS
*/
void config_uart (void);
void recepcion_de_paquetes (void);
uint8 rfReadRxPacket(uint8 *pBuf, uint8 maxLen);
uint8 rfReadRxPacketCB(circular_buffer *cb);


uint8 rfReadRxPacket(uint8 *pBuf, uint8 maxLen) {
    uint8 length;
    uint8 i;
    if (RFFSTATUS & RXAVAIL) {
        length = RFD;
        for (i = 0; i < length; i++) {
            uint8 byte = RFD;
            if (i < maxLen) {
                pBuf[i] = byte;
            }
        }
    }
    return length;
}

uint8 rfReadRxPacketCB(circular_buffer *cb) {
    uint8 length;
    uint8 i;
    if (RFFSTATUS & RXAVAIL) {
        length = RFD;
        for (i = 0; i < length; i++) {
            uint8 byte = RFD;
            cb_push_back(cb, &byte);
        }
    }
    return length;
}


#pragma vector=RF_VECTOR
__interrupt void rf_IRQ(void)
{ 
    rfReadRxPacketCB(&cb);

    // Clear RF interrupts.
    RFIRQF1 = 0;
    S1CON = 0;
  
    halRfStartRx();
}

void debugArrayInit()
{
  for (int i = 0; i < DEBUG_BUFFER_SIZE; i++)
  {
      debugArray[i] = 0xFF;
  }
}
  
/*******************************************************************************
* @fn           main
*
* @brief        Llamado de fuinciones.
*
* @param        void
*
* @return       none
*/
int main(void) 
{
#if USE_DEBUG_BUFFER
      debugArrayInit();
#endif
      cb_init(&cb, 128, 1);
      config_uart();
      recepcion_de_paquetes();

      while(1);
}


/*******************************************************************************
* @fn           config_uart
*
* @brief        Configura el clock y el módulo UART.
*
* @param        void
*
* @return       none 
*/
void config_uart (void)
{
 
	// Configura HS XOSC como fuente del system clock sin pre-scaling.
	CLKCONCMD = (CLKCONCMD & ~(CLKCON_OSC | CLKCON_CLKSPD)) | CLKCON_CLKSPD_32M;

	// Espera hasta que la configutacion del clock haya finalizado
	while (CLKCONSTA & CLKCON_OSC);    

	// Configuracion de pines de I/O para utilizar SPI
	P0SEL0 = 0x11;         
	P0SEL1 = 0x11;        

	/**
	* Configuración UART
	*
	*/

	// Establece bitrate a 2 mbps.
	U0BAUD = UART_BAUD_M;
	U0GCR = (U0GCR & ~U0GCR_BAUD_E) | UART_BAUD_E;

	// Inicializa protocolo UART (bit start/stop, bits de datos, paridad, etc.)
	U0CSR |= U0CSR_MODE;

	// Nivel bajo en bit de inicio => Nivel alto para ocioso.
	U0UCR &= ~U0UCR_START;

	// Bit de parada = alto (U0UCR.STOP = 1).
	U0UCR |= U0UCR_STOP;

	// Número de bits de parada = 1 (U0UCR.SPB = 0).
	U0UCR &= ~U0UCR_SPB;

	// Paridad deshabilitada (U0UCR.PARITY = 0).
	U0UCR &= ~U0UCR_PARITY;

	// 9-bits de datos = 8 bits de transferencia (U0UCR.BIT9 = 0).
	U0UCR &= ~U0UCR_BIT9;

	U0UCR &= ~U0UCR_D9;

	// Control flow = deshabilitado (U0UCR.FLOW = 0).
	U0UCR &= ~U0UCR_FLOW;

	// Orden de bits = LSB primero (U0GCR.ORDER = 0).
	U0GCR &= ~U0GCR_ORDER;

	halIntOn();
}

/*******************************************************************************
* @fn           recepcion_de_paquetes
*
* @brief        Recibe los paquetes por RF y los retransmite por UART.
*
* @param        void
*
* @return       none
*/
void recepcion_de_paquetes (void) 
{
#if USE_DEBUG_BUFFER
    static int j = 0;
#endif

    // Configuración RF como Rx.
    halRfDisableRadio (FORCE);
    halRfInit ();
	halRfConfig (GFSK_2Mbps_500khz, RX, 32, PKT_CONF_MODE_BASIC_VARLEN);
	halRfSetFrequency (2402); 
    halRfSetCrc (CRC_16_CCITT);
    halRfSetSyncWord (SYNCWORD, 0);
    halRfSetRxAddress (0, ADDR_CONF_RX_AUTO_SW1, 0xEF, 32);
    halRfEnableRadio ();

	// Habilita interrupciones RF.
	//halRfEnableInterrupt (RFIRQF1_RXOK);
	halRfEnableInterrupt (RFIRQF1_TASKDONE);

	// Habilita interrupciones globales.
	halIntOn ();

	halRfStartRx(); 

	while (1) 
        {
          size_t count = cb.count;
          
          if (count > 0)
          {
              // Limpia cualquier pedido de interrupcion pendiente de TX.
              U0CSR &= ~U0CSR_TX_BYTE;
              
              for (int i = 0; i < count; i++) 
              {
                  uint8 aux; 
                  cb_pop_front(&cb, &aux);
                  U0DBUF = aux; 
                
#if USE_DEBUG_BUFFER
                  if (j < DEBUG_BUFFER_SIZE)
                  {
                      debugArray[j] = aux;
                      j++;
                  }
#endif
                  
                  // Verifica si el byte es transmitido  
                  while (!(U0CSR & U0CSR_TX_BYTE));

                  // Limpia el estado del byte transmitido.
                  U0CSR &= ~U0CSR_TX_BYTE;
              }
          }          
          
          
/*		// Inicia la recepción de paquetes.
		halRfStartRx(); 

		// Espera en loop por TASKDONE (finalización de tarea).
		while (!(rfirqf1 & RFIRQF1_TASKDONE));

                // Limpia cualquier pedido de interrupcion pendiente de TX.
                U0CSR &= ~U0CSR_TX_BYTE;

                // Transmite por UART los paquetes recibidos por RF.
                length = RFD;
                for (i = 0; i < length; i++) {
                    byte = RFD;
                    U0DBUF = byte; 

                    if (j < DEBUG_BUFFER_SIZE)
                    {
                        debugArray[j] = byte;
                        j++;
                    }
                    
                    // Verifica si el byte es transmitido  
                    while (!(U0CSR & U0CSR_TX_BYTE));

                    // Limpia el estado del byte transmitido.
                    U0CSR &= ~U0CSR_TX_BYTE;
                }
                
		// Limpia interrupciones.
		rfirqf1 = 0;

		// Limpia la FIFO RX de RF.
		//SEND_LLE_CMD (CMD_RXFIFO_RESET); */
	}
}