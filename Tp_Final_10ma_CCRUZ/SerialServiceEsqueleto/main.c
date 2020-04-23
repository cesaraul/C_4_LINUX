//==TP2
//==SISTEMAS OPERATIVOS DE PROPOSITO GENERAL
//==CESAR CRUZ GUTIERREZ
/*1) Deberias pasar conx_socket de nuevo a -1 cuando la conexion se cierra, sino desde el thread q recibe por la uart, 
seguis haciendo write a un socket que esta cerrado. Fijate de controlar la lectura de este conx_socket con un mutex en el thread de la relceion de la uart

2) tambien en el handler de la signal haces el close de conx_socket pero no sabes si tiene un valor valido para hacer unclose

3) los mutex estan mal usados, los usas siempre en el mismo thread, no tiene sentido que esten. lo que podrias protejer con el mutex es conx_socket que es la unica variable que compartis entre los dos threads.*/
//========================================
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "main.h"
#include "SerialManager.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <signal.h>
#include <pthread.h>



char Buffer[ BUFFER_SIZE ];			  // buffer de DATOS
int sv_socket;						  // FD de socket server para escuchar conexiones nuevas
int conx_socket; 				   	 // FD de socket server para leer y escribir el socket
pthread_t threadI;			  	     // array para los threads

pthread_mutex_t mutex_net = PTHREAD_MUTEX_INITIALIZER;	//   mutex para datos sockets
 

//============ functions declaration
void bloquearSign( void ) // funcion bloqueo de señales
{
	sigset_t set;

	sigemptyset( &set );
	sigaddset( &set, SIGINT );
	sigaddset( &set, SIGTERM );
	pthread_sigmask( SIG_BLOCK, &set, NULL );
}


void desbloquearSign( void )// funcion de desbloqueo de señales
{
	sigset_t set;

	sigemptyset( &set );
	sigaddset( &set, SIGINT );
	sigaddset( &set, SIGTERM );
	pthread_sigmask( SIG_UNBLOCK, &set, NULL );
}

 void sigint_handler( int sig ) // handler para manejar SIGINT
{
	//pthread_cancel( threadI );
	//pthread_join( threadI, NULL );
	close( conx_socket );
	//close( sv_socket );
	//printf( "end server \n" );
	//exit( 1 );
}

void * rx_net_tx_uart( void * parameters )// funcion para recepcion en socket y envio a uart
{
	int len;
 
while(1)
	{
		 

		len = read( conx_socket, Buffer, BUFFER_SIZE );
	 

		if( len == -1 )
		{
			perror( "read socket error!!" );
			exit (1);
		}

		else if ( len == 0 )
		{	
			
			printf( "conecction closed\n" );
			close( conx_socket );
			pthread_mutex_lock(&mutex_net);
			conx_socket= -1 ; //=====error 1

			pthread_mutex_unlock(&mutex_net);

			return "";
		}

		Buffer[ len ] = '\0';
		printf( "received by socket %s\n", Buffer ); //

 

		serial_send( Buffer, len ); // envio de datos
 
	}

	return "";
}

void * rx_uart_tx_net( void * parameters ) //funcion para recibir de uart y trnasmitir a socket
{
	int len;

while(1)
	{

		len = serial_receive( Buffer, BUFFER_SIZE );

 		if( len > 0 && conx_socket > 0 ) 
		{
			Buffer[ len - 2 ] = '\0';
			printf( "received by uart %s\n", Buffer );

 			if( write( conx_socket, Buffer, strlen( Buffer ) ) == -1 )
			{
				perror( "socket write error!!" );
				return "";
			}
		}
 		usleep( POLLING_TIME );
	}

	return "";
}




//===================== FUncion principal

int main()
{
	/* se declaran las estructuras y variables para el socket */
	socklen_t addrlen;
	struct sockaddr_in client_address;
	struct sockaddr_in server_address;
	struct sigaction sa;

	//===SIGINT SIGTERM, configuracion y validación
    sa.sa_handler = sigint_handler;
    sa.sa_flags = 0;
    if( sigemptyset( &sa.sa_mask ) == -1)
    {
        perror( "sigemptyset_error!!" );
        exit( 1 );
    }
    if( sigaction( SIGINT, &sa, NULL ) == -1 )
    {
        perror( "sigaction error!!" );
        exit( 1 );
    }

    if( sigemptyset( &sa.sa_mask ) == -1)
    {
        perror( "sigemptyset error!!" );
        exit( 1 );
    }
    if( sigaction( SIGTERM, &sa, NULL ) == -1 )
    {
        perror( "sigaction error!!" );
        exit( 1 );
    }
///============================fin de configuración


	bloquearSign();//==bloqueo de señales

 	if( serial_open( SER_NB, BAUDRATE ) == 1 )
		exit( 1 );

 	sv_socket = socket( PF_INET,SOCK_STREAM, 0 );

	///=======configuración de parametros del servidor
    bzero( ( char * )&server_address, sizeof( server_address ) );
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons( PORT_NB );
    server_address.sin_addr.s_addr = inet_addr( ADDRESS );

 	if( server_address.sin_addr.s_addr == INADDR_NONE )
    {
        fprintf( stderr, "error on IP server \n" );
        exit( 1 );
    }

 	if ( bind( sv_socket, ( struct sockaddr * )&server_address, sizeof( server_address ) ) == -1 )
	{
		close( sv_socket );
		perror( "bind error!!" );
		exit( 1 );
	}

 	if ( listen( sv_socket, LISTE_BACKLOG ) == -1 )
  	{
    	perror( "listen error!!" );
    	exit( 1 );
  	}
//======================================= error 2 (void*) (intptr_t) conx_socket
 	if(pthread_create ( &threadI, NULL, rx_uart_tx_net, NULL )!= 0)
	{		close(conx_socket);
		    printf("error while create thread\n");
            
            return 0;
			//return -1
	}
 	desbloquearSign();

 while(1)
	{
 		printf( "wating for conecctions...\n" );
		addrlen = sizeof( struct sockaddr_in );

		pthread_mutex_lock(&mutex_net);
		conx_socket = accept( sv_socket, ( struct sockaddr * )&client_address, &addrlen );
		pthread_mutex_unlock(&mutex_net);

		if ( conx_socket == -1 )
		{	
			if (pthread_cancel(threadI)!=0)
			{
				printf("culdn't cancel thread\n");
			}  

 			if (pthread_join(threadI, NULL)!=0)
			{
				printf("Couldn't join\n");
			}

 			close( sv_socket );
			//printf( "end server \n" );
			//exit( 1 );
			perror( "end server... \n" );

			exit(1);
		}
		// nueva conexion
		printf  ( "new conecction: %s\n", inet_ntoa( client_address.sin_addr ) );

 		rx_net_tx_uart( NULL );
	}

	return 0;
}
