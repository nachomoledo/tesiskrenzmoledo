/* TRANSMISOR */

/*******************************************************************************
* INCLUDES
*/

// Definiciones de bits individuales de los registros de los dispositivos CC254x.
#include <ioCC254x_bitdef.h>

// Incluye archivos especificos de CC2544.
#include "ioCC2544.h"

//Definiciones de tipo HAL.
#include <hal_types.h> 

// Funciones HAL.
#include "hal_rf_proprietary.h" 
#include "hal_int.h"
#include "hal_timer2.h"
#include "circular_buffer.h"

/*******************************************************************************
* CONSTANTES
*/

// Palabra de sincronizacion (iguales en ambos dispositivos).
#define SYNCWORD 0x29417671

// Con estos valores, se obtiene un baudrate de 2.00 Mbps con un clock de 32 MHz.
//#define SPI_BAUD_M  0
//#define SPI_BAUD_E  16

// Con estos valores, se obtiene un baudrate de 115200 con un clock de 32 MHz.
#define SPI_BAUD_M  216
#define SPI_BAUD_E  11

// Utilizado para crear un buffer.
#define BUFFER_SIZE 29
#define DEBUG_BUFFER_SIZE 512

#define USE_DEBUG_BUFFER 1


/*******************************************************************************
* VARIABLES
*/
extern volatile uint8 rfirqf1; // Bandera de interrupcion.
//static uint8 receive_spi_complete = 0; // Bandera para enviar cuando se recibió el último dato por SPI.
//static uint8 bufferIndex = 0;
//static uint8 len = 0;
//static uint32 timer = 0;
//static char SpiRxBuffer[BUFFER_SIZE]; // Buffer de recepción RF.
static circular_buffer cb;

#if USE_DEBUG_BUFFER
static char debugArray[DEBUG_BUFFER_SIZE];
#endif

/*******************************************************************************
*  FUNCIONES
*/
void config_spi (void);
void config_rf (void);
void send_bytes (void);
uint8 rfPrepareTxPacketCB(uint8 len, circular_buffer *cb);
//void transmision_de_paquetes (void);
//void transmision_test (void);


/*******************************************************************************
* @fn          uart0rx_isr
*
* @brief       Rutina de interrupción que recibe los datos por SPI y los 
*              almacena en un buffer auxiliar.
*
* @param       none
*
* @return      none
*/
#pragma vector = URX0_VECTOR
__interrupt void uart0rx_isr (void)
{   
    // Escribe byte recibido al buffer.
    char c = U0DBUF;
    cb_push_back(&cb, &c);
}

/*#pragma vector = URX0_VECTOR
__interrupt void uart0rx_isr (void)
{
    // Resetea Timer.
    timer = 0;
    
    // Escribe byte recibido al buffer.
    SpiRxBuffer[bufferIndex++] = U0DBUF;
    
    // Si el buffer se llena, comienza transmision por RF.
    if (bufferIndex == BUFFER_SIZE) {
       len = bufferIndex;
       bufferIndex = 0;
       receive_spi_complete = 1;
    }  
}*/

/*******************************************************************************
* @fn           main
*
* @brief        Llamado de fuinciones.
*
* @param        void
*
* @return       none
*/
int main (void) 
{
    cb_init(&cb, 128, 1);
    config_spi ();
    config_rf();
    send_bytes();
    //transmision_de_paquetes ();
    //transmision_test();
    while (1);
}


/*******************************************************************************
* @fn           config_spi
*
* @brief        Configura el clock y el módulo SPI.
*
* @param        void
*
* @return       none 
*/
void config_spi (void)
{
    // Configura HS XOSC como fuente del system clock sin pre-scaling.
    CLKCONCMD = (CLKCONCMD & ~(CLKCON_OSC | CLKCON_CLKSPD)) | CLKCON_CLKSPD_32M;
    
    // Espera hasta que la configutacion del clock haya finalizado.
    while (CLKCONSTA & CLKCON_OSC);    
    
    // Configuracion de pines de I/O para utilizar SPI.
    P0SEL0 = 0x11;         
    P0SEL1 = 0x11;      
  
    /**
    * Configuración de interrupciones
    */

    // Limpia el flag de interrupción de CPU para USART0 RX (TCON.URX0IF).
    URX0IF = 0;
    // Habilita interrupciones de USART0 RX seteando [IEN0.URX0IE=1].
    URX0IE = 1;
    // Habilita interrupciones globales.
    EA = 1;

    /**
    * Configuración SPI
    */
    
    // Configura SPI como esclavo.
    U0CSR = (U0CSR & ~U0CSR_MODE) | U0CSR_SLAVE;

    // Configura:
    // - Valor de mantisa.
    // - Valor del exponente.
    // - Centrar la fase del clock en el primer flanco del periodo SCK.
    // - Polaridad negativa del clock (SCK estado bajo en inactividad).
    // - Orden de bit LSB primero.
    U0BAUD =  SPI_BAUD_M;
    U0GCR = (U0GCR & ~(U0GCR_BAUD_E | U0GCR_CPOL | U0GCR_CPHA)) | U0GCR_ORDER
            | SPI_BAUD_E;
    
    halIntOn();
}

/*******************************************************************************
* @fn           transmision_de_paquetes
*
* @brief        Cuando por SPI se haya recibido un paquete completo, se lo
*               envía por RF.
*
* @param        void  
*
* @return       none
*/
#if 0
void transmision_de_paquetes (void) 
{  
    int k = 0;

    // Configuración RF como Tx.
    halRfDisableRadio (FORCE);
    halRfInit ();
    halRfConfig (GFSK_2Mbps_500khz, TX, 32, PKT_CONF_MODE_BASIC_VARLEN);
    //halRfSetFrequency (2402);
    halRfSetCrc (CRC_16_CCITT);
    halRfSetSyncWord (SYNCWORD, 0);
    halRfSetTxAddress (0xEF, ADDR_CONF_TX_AUTO, 16);
    PRF.ADDR_ENTRY[0].CONF.REUSE = 1;
    halRfSetFrequency (2402);
    halRfEnableRadio ();
    
    // Habilita interrupciones RF.
    halRfEnableInterrupt (RFIRQF1_TASKDONE);
    
    // Habilita interrupciones globales.
    halIntOn ();
    
    
                    /* Si no coincide el tamaño del paquete, resetea la FIFO y 
                   continua cargando y enviando otro paquete. */
                //halRfCommand(CMD_RXFIFO_RESET);
    
        // Configuración de radio para transmitir paquetes cada 10 ms.
    //halRfPacketTxInterval (VALUE_10MS_IN_1US_UNITS);
    

    while (1) {
      
        // Si expiró el time_out (500 ms), terminó.
        if ((timer == 150000) && (bufferIndex > 0)) {
          
            receive_spi_complete = 1;
            len = bufferIndex;
        } else if(timer == 150000) {
          timer = 0;
        }

        /* Espera a que se haya recibido por SPI un paquete entero para 
        luego enviarlo por RF. Si bandera = 1, listo para enviar */
        if (receive_spi_complete) {

            receive_spi_complete = 0;
            
            RFD = len;
            // Escribe los datos en la FIFO de RF.
            for (k = 0; k < len; k++) {
                RFD = SpiRxBuffer[k];
            }

            // Inicia la transmisión.            
            halRfStartTx();

            // Espera en loop por TASKDONE (finalización de tarea).
            while (!(rfirqf1 & RFIRQF1_TASKDONE)) {}

            // Verifica si la tarea terminó correctamente.
            if (PRF.ENDCAUSE == TASK_ENDOK) {
                // Limpia interrupciones.
                rfirqf1 = 0;
            }

            // Limpia la FIFO de RF.
            SEND_LLE_CMD(CMD_TXFIFO_RESET);

            // Limpia el buffer para receibir nuevos paquetes por SPI.   
            memset (SpiRxBuffer, '\0', BUFFER_SIZE * sizeof (uint8));
        } 
        
        timer++;
    }
}
#endif

void config_rf (void) 
{  
    // Configuración RF como Tx.
    halRfDisableRadio (FORCE);
    halRfInit ();
    halRfConfig (GFSK_2Mbps_500khz, TX, 32, PKT_CONF_MODE_BASIC_VARLEN);
    //halRfSetFrequency (2402);
    halRfSetCrc (CRC_16_CCITT);
    halRfSetSyncWord (SYNCWORD, 0);
    halRfSetTxAddress (0xEF, ADDR_CONF_TX_AUTO, 16);
    PRF.ADDR_ENTRY[0].CONF.REUSE = 1;
    halRfSetFrequency (2402);
    halRfEnableRadio ();
    
    // Habilita interrupciones RF.
    halRfEnableInterrupt (RFIRQF1_TASKDONE);
    
    // Habilita interrupciones globales.
    halIntOn ();
}

uint8 rfPrepareTxPacketCB(uint8 len, circular_buffer *cb)
{
#if USE_DEBUG_BUFFER
    static int j = 0;
#endif
    // Check that the packet can fit in the FIFO
    if (RFTXFLEN > 127 - len) {
        return 0;
    }
    // Enter length
    RFD = len;
    // Enter packet if pointer is provided. If pointer is NULL, data should be 
    // entered by writing to RFD
    if (cb) {
        for (int i = 0; i < len; i++) 
        {
            uint8 aux; 
            cb_pop_front(cb, &aux);
            RFD = aux;
#if USE_DEBUG_BUFFER
            if (j < DEBUG_BUFFER_SIZE)
            {
                debugArray[j] = aux;
                j++;
            }
#endif
        }
    }
    return len;
}

void send_bytes(void)
{
      while (1) 
      {
          uint8 bytesToSend = 0;
          
          size_t count = cb.count;
          
          if (count > 0)
          {
              halMcuWaitMs(10);

              bytesToSend = rfPrepareTxPacketCB(count, &cb);
              
              if (bytesToSend > 0) 
              {       
                  // Inicia la transmisión.            
                  halRfStartTx();

                  // Espera en loop por TASKDONE (finalización de tarea).
                  while (!(rfirqf1 & RFIRQF1_TASKDONE)) {}

                  // Verifica si la tarea terminó correctamente.
                  if (PRF.ENDCAUSE == TASK_ENDOK) {
                      // Limpia interrupciones.
                      rfirqf1 = 0;
                  }

                  // Limpia la FIFO de RF.
                  SEND_LLE_CMD(CMD_TXFIFO_RESET);
              }
          }
      }
}
#if 0
void transmision_test (void) 
{  
    const char mensaje[33] = "~1234567891234567891234567891234}";
//    const char mensaje[4] = "hola";
    int k = 0;

    // Configuración RF como Tx.
    halRfDisableRadio (FORCE);
    halRfInit ();
    halRfConfig (GFSK_2Mbps_500khz, TX, 32, PKT_CONF_MODE_BASIC_VARLEN);
    //halRfSetFrequency (2402);
    halRfSetCrc (CRC_16_CCITT);
    halRfSetSyncWord (SYNCWORD, 0);
    halRfSetTxAddress (0xEF, ADDR_CONF_TX_AUTO, 16);
    PRF.ADDR_ENTRY[0].CONF.REUSE = 1;
    halRfSetFrequency (2402);
    halRfEnableRadio ();
    
    // Habilita interrupciones RF.
    halRfEnableInterrupt (RFIRQF1_TASKDONE);
    
    // Habilita interrupciones globales.
    halIntOn ();
    
    
                    /* Si no coincide el tamaño del paquete, resetea la FIFO y 
                   continua cargando y enviando otro paquete. */
                //halRfCommand(CMD_RXFIFO_RESET);
    
        // Configuración de radio para transmitir paquetes cada 10 ms.
    //halRfPacketTxInterval (VALUE_10MS_IN_1US_UNITS);
    

    while (1) {
      
        // Si expiró el time_out (500 ms), mandar mensaje.
        if (timer >= 150000) 
        {
            receive_spi_complete = 1;
            timer = 0;
        }

        /* Espera a que se haya recibido por SPI un paquete entero para 
        luego enviarlo por RF. Si bandera = 1, listo para enviar */
        if (receive_spi_complete) {

            receive_spi_complete = 0;
            
            RFD = 33;
//            RFD = 4;
            // Escribe los datos en la FIFO de RF.
            for (k = 0; k < 33; k++) {
//            for (k = 0; k < 4; k++) {
                RFD = mensaje[k];
            }

            // Inicia la transmisión.            
            halRfStartTx();

            // Espera en loop por TASKDONE (finalización de tarea).
            while (!(rfirqf1 & RFIRQF1_TASKDONE)) {}

            // Verifica si la tarea terminó correctamente.
            if (PRF.ENDCAUSE == TASK_ENDOK) {
                // Limpia interrupciones.
                rfirqf1 = 0;
            }

            // Limpia la FIFO de RF.
            SEND_LLE_CMD(CMD_TXFIFO_RESET);
        } 
        
        timer++;
    }
}
#endif