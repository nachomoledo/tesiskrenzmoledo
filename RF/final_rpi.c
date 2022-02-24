/*******************************************************************************
* INCLUDES
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>


/*******************************************************************************
* CONSTANTES
*/
#define BUFFER_SIZE 127 //tamaño de los paquetes a enviar.


/*******************************************************************************
* VARIABLES
*/
int fd; //Descriptor del SPI.
unsigned char result; //Valor leido por SPI.


/*******************************************************************************
* FUNCIONES
*/
int spiTxRx (unsigned char txDat);


/*******************************************************************************
* @fn           main
*
* @brief        Abre el puerto SPI. Abre la imagen y calcula cuantos bytes ocupa.
*               Luego lee la misma en paquetes de tamaño "BUFFER_SIZE" y los
*               envía por SPI.
*
* @param        *argv[1] Nombre de la imagen a enviar.
*
* @return       0
*/
int main (int argc, char *argv[])
{
    unsigned int speed = 2000000;
    FILE * filer;
    int i = 0;
    int numr;
    char buffer[BUFFER_SIZE];
    long length;

    //Verifica que se haya pasado como parametro el nombre de la imagen.
    if (argc != 2) {
        fprintf (stderr, "\n%s\n", "Colocar nombre de imagen a enviar.");
        exit (1);
    }

    //Abre el puerto SPI.
    fd = open ("/dev/spidev0.0", O_RDWR);
    //Establece velcidad de enlace SPI.
    ioctl (fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);

    //Abre la imagen a leer.
    if ((filer = fopen (argv[1],"rb")) == NULL) {
        fprintf (stderr, "\nNo se puedo abrir la imagen.\n");
        exit (1);
    }

    //Recorre la imagen y almacena en "lenght" el tamaño de la misma en bytes.
    fseek (filer,0L,SEEK_END);
    length = ftell(filer);
    //Regresa el puntero al comienzo del archivo imagen.
    fseek (filer, 0, SEEK_SET);

    //Envío por SPI el tamaño del archivo desglosado en 4 bytes.
    spiTxRx ((char) (length & 0xFF));
    spiTxRx ((char) ((length >> 8) & 0xFF));
    spiTxRx ((char) ((length >> 16) & 0xFF));
    spiTxRx ((char) ((length >> 24) & 0xFF));

    //Envío por SPI el tamaño de los paquetes a enviar.
    spiTxRx ((char) BUFFER_SIZE);

    printf ("\nEstableciendo conexion...\n");

    /* Envía cada 100ms un caracter 'n', esperando como respuesta un caracter
    'y'. Si el caracter 'y' fue recibido, significa que se estableció la 
    conexion entre las placas RfTx y RfRx */ 
    do {
        result = spiTxRx ((char) 'n');
        usleep (100000);
    } while (result != 'y');

    printf("Conexion establecida\nTransmitiendo imagen...\n");

    usleep(1000000);

    /* Recorre toda la imagen. Almacena en "buffer" un paquete de tamaño
      "BUFFER_SIZE" y luego envía ese paquete byte a byte por SPI. Se 
      realizó de esta manera, para no tener que estar accediendo
      constantemente al archivo imagen para enviar de a bytes. */
    while (feof (filer) == 0) {

        //Delay entre paquete y paquete.
        usleep (950); 

        //Se lee un paquete.
        if ((numr = fread (buffer, 1, BUFFER_SIZE, filer)) != BUFFER_SIZE) {
            if (ferror (filer) != 0) {
                fprintf (stderr,"read file error.\n");
                exit (1);
            }
            else if (feof (filer) != 0);
        }

        //Se envía byte a byte el paquete por SPI. 
        for (i = 0; i < BUFFER_SIZE; i++) {
            result = spiTxRx (buffer[i]);
        }
    } 
    //Se cierra el archivo imagen.
    fclose (filer);
    printf ("%s\n", "Imagen transmitida con exito.");

    return 0;
}


/*******************************************************************************
* @fn           spiTxRx
*
* @brief        Envía por SPI el caracter pasado como parámetro y devuelve el 
*               caracter leído en ese instante de tiempo.
*
* @param        txDat Byte a enviar por SPI.
*
* @return       rxDat Byte recibido.
*/
int spiTxRx (unsigned char txDat)
{
 
    unsigned char rxDat;
    //Estructura que contendrá los valores a recibir y enviar.
    struct spi_ioc_transfer spi;
    memset (&spi, 0, sizeof (spi));

    spi.tx_buf        = (unsigned long)&txDat;
    spi.rx_buf        = (unsigned long)&rxDat;
    //Longitud de los datos.
    spi.len           = 1;

    ioctl (fd, SPI_IOC_MESSAGE(1), &spi);

    return rxDat;
}
