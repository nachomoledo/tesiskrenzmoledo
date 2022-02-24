/*******************************************************************************
* INCLUDES
*/
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/*******************************************************************************
* CONSTANTES
*/
#define ERROR_OPEN_PORT -1


/*******************************************************************************
* FUNCIONES
*/
int inicio_serie (char *nombre_serie, int baudios);
int leer_serie (int serial_fd, char *datos, int tamanio, int timeout_usec);


/*******************************************************************************
* @fn           main
*
* @brief        Abre el puerto serie. Crea el archivo de salida de la imagen
*				y almacena en él los datos provenientes del puerto serie.
*
* @param        *argv[1] Numero de puerto serie a leer.
*
* @return       -1 Error
*				0  Exitoso
*/
int main (int argc, char *argv[])
{	

	int fd;
	unsigned char t;
	unsigned char buffer_size;
	unsigned char n_bytes_archivo[4];
	unsigned char tam_buf[1];
	unsigned long n_bytes;
	FILE *filew;
	int numw;
	int paquete = 1;
	int estado = 0;

	//Verifica que se haya pasado como parametro el numero de puerto.
	if (argc != 2) {
		fprintf (stderr, "%s\n", "Colocar numero de puerto");
		exit (1);
	}

  	printf ("\nEstableciendo conexión...\n");

  	char portname[13] = "/dev/ttyUSB";
  	//Concatena la variable "portname con el numero de puerto.
  	strcat (portname, argv[1]);

  	//Abre puerto serie
	fd = inicio_serie (portname, B2000000);
	if (fd < 0) {
		printf ("Error opening %s: %s\n", portname, strerror (errno));
		return -1;
	}

	//Cierra y crea un nuevo archivo para limpiarlo.
	fclose (fopen (portname, "w"));

	//Espera a recibir el carácter '\0' proveniente del puerto serie
	do {
		read (fd, &t, 1);
	} while (t != '\0');

	//Leo cantidad de bytes de la imagen.
	leer_serie (fd, n_bytes_archivo, 4, 100000); 
	//Leo el tamaño de los paquetes a recibir.
	leer_serie (fd, tam_buf, 1, 100000); 

	buffer_size = tam_buf[0];

	//Almaceno en "n_bytes" el numero de bytes de la imagen a recibir
	n_bytes = n_bytes_archivo[0]; 
	n_bytes |= (((long) n_bytes_archivo[1] << 8) & 0xFF00);  
	n_bytes |= (((long) n_bytes_archivo[2] << 16) & 0xFF0000);  
	n_bytes |= (((long) n_bytes_archivo[3] << 24) & 0xFF000000); 

	/* Se realiza la division entre el numero de bytes de la imagen con
	el tamaño de los paquetes a recibir para calcular cuantos paquetes
	se recibiran */
	unsigned int paquetes = (n_bytes / buffer_size) + 1;
	/* El ultimo paquete a recibir, contendra bytes de descarte que se 
	agregaron para que el tamaño de los paquetes sea constante. Con la 
	variable "resto", calcularemos cuales son los bytes de carga útil
	para reconstruir la imagen tal cual se envió. */
	unsigned int resto = n_bytes % buffer_size;

	printf ("Tamaño de paquete (bytes): %d\n", buffer_size);
	printf ("Paquetes a recibir: %d \n", paquetes);
	printf ("Conexión establecida.\nRecibiendo imagen...\n");

  	//Se crea el archivo de salida.
	if ((filew = fopen ("reconstruccion.jpg", "wb")) == NULL) {
		fprintf (stderr, "open write file error.\n");
		exit (1);
	} 

	//Se lee el tiempo actual para saber cuanto tarda en recibir la imagen.
	time_t seconds = time(NULL);

	int tam = (int) buffer_size;
	//Buffer donde se almacenarán los datos recibidos.
	unsigned char buf[tam];

	do {

		/* Leo el puerto serie y almaceno en "buf" la cantidad de datos igual
		a "tam". 4 segundos para leer los datos, si no se lee en ese tiempo
		la funcion devuelve un 0 */
		estado = leer_serie (fd, buf, tam, 4000000); 

		if (estado == 0) {
			printf ("Se agotó el tiempo de espera. Paquetes recibidos %d/%d. " 
					"Repetir transmisión.\n", paquete-1, paquetes);
			fclose (filew);
			close (fd);
			exit (1);
		}

		/* Se almacenan los datos de los paquetes en la imagen de salida. 
		Para el último paquete, se recalcula la cantidad de datos a escribir
		para que la imagen recibida sea exactamente igual a la enviada. */
		if (paquete < paquetes) {
			
			if ((numw = fwrite (buf,1,buffer_size,filew)) != buffer_size) {
				fprintf (stderr, "write file error.\n");
				exit (1);
			}
			paquete++;
		} 
		else {

			if ((numw = fwrite (buf,1,resto,filew)) != resto) {
				fprintf (stderr, "write file error.\n");
				exit (1);
			}
			paquete++;
		}

	} while (paquete <= paquetes);

	time_t seconds2 = time (NULL);
	fclose (filew);
	close (fd);
	printf ("Imagen recibida con éxito en %ld segundos.\n", seconds2 - seconds);
	return 0;
}


/*******************************************************************************
* @fn           inicio_serie
*
* @brief        Abre el puerto serie para lectura/escritura. Configura velocidad
*
* @param        *nombre_serie Descriptor del puerto serie.
*				baudios Velocidad de trabajo.
*
* @return       fd Devuelve el descriptor del puerto serie (o -1 si ha ocurrido 
*				un error).
*                   
*/
int inicio_serie (char *nombre_serie, int baudios)
{
	//Estructura donde se setean los parametros del puerto.
	struct termios newtermios;  
	//Descriptor del puerto serie.  
	int fd;                       

	//Abro el puerto serie.
	fd = open (nombre_serie, O_RDWR | O_NOCTTY);

	//Configuro el puerto serie.
	newtermios.c_cflag = CBAUD | CS8 | CLOCAL | CREAD;
	newtermios.c_iflag = IGNPAR;
	newtermios.c_oflag = 0;
	newtermios.c_lflag = 0;
	newtermios.c_cc[VMIN] = 1;
	newtermios.c_cc[VTIME] = 0;

	//Establezco la velocidad de trabajo
	cfsetospeed (&newtermios, (speed_t) baudios);
	cfsetispeed (&newtermios, (speed_t) baudios);

	//Vacío el buffer de entrada.
	if (tcflush (fd, TCIFLUSH) == -1) {
		return (ERROR_OPEN_PORT);
	}
	//Vacío el buffer de salida.
	if (tcflush (fd, TCOFLUSH) == -1) {
		return (ERROR_OPEN_PORT);
	}
	//Configuracion del puerto serie.
	if (tcsetattr (fd, TCSANOW, &newtermios) == -1) {
		return (ERROR_OPEN_PORT);
	}

	//Retorno el descriptor de puerto serie.
	return (fd);
}


/*******************************************************************************
* @fn           leer_serie
*
* @brief        Lee datos del puerto serie.
*
* @param        serial_fd Descriptor del puerto serie.
*				*datos Buffer contenedor de datos recibidos.
*				tamanio Tamaño maximo de datos a recibir.
*				timeout_usec Tiempo maximo para recibir datos.
*
* @return       count Devuelve el número de bytes leídos (o 0 si ha ocurrido un 
*				timeout).                 
*/
int leer_serie(int serial_fd, char *datos, int tamanio, int timeout_usec)
{
	fd_set fds;                    
	struct timeval timeout;	//Tiempo de espera datos.
	int count = 0;          //Controla la cant de bytes que ingresan en *datos.
	int ret;                //Indico si hay datos a leer.
	int n;                  //Bytes leidos.

	/*Espera a que llegue un bloque de bytes del tamaño establecido en el plazo
	determinado por timeout_usec. */
	do {

		//Set de descriptores del puerto serie.
		FD_ZERO (&fds);
		FD_SET (serial_fd, &fds);

		timeout.tv_sec = 0;  
		timeout.tv_usec = timeout_usec;

		/* Devuelve 1 si hay datos esperando a ser leídos y 0 si ha ocurrido un 
		timeout. Sin el select() quedaría bloqueado esprando a que termine el 
		tiempo o se envie todo el paquete */
		ret = select (FD_SETSIZE, &fds, NULL, NULL, &timeout);

		//Si hay datos los lee hasta que acabe el tiempo o lea todos los datos.
		if(ret == 1){
			n = read (serial_fd, &datos[count], tamanio - count);
			count = count + n;
		}

	} while ((count < tamanio) && (ret == 1));

	//Retorno la cantidad de bytes leidos.
	return (count);
}










