
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_NAME               "myfifo"

#define ARCHIVO_SIGN            "./Sign.txt"
#define ARCHIVO_LOG             "./Log.txt"
//---ERRORES
#define E_MKNOD             -1
#define E_OPEN_FIFO         -2
#define E_FGETS             -3
#define E_OPEN_SIGN         -4
#define E_OPEN_LOG          -5
#define E_WRITER_CERRADO    -6
#define E_READ_FIFO         -7



volatile sig_atomic_t fd; //--- Archivo de la FIFO


// Funciones

void sigint_handler(int sig)
{
   write(0, "\nSe recibio SIGINT...\n", sizeof("\nSe recibio SIGINT...\n"));

}


int main(void)//-INICIO MAIN
{
   	char cad[300];
    int n;
    struct sigaction sa;
    char cad_bis [300];

    FILE* fdSign, *fdLog;//--- archivos de escritura

    printf("Sistemas Operativos de Proposito General\n");
    printf("TP1 programa [reader]\n\n");

    printf("Instalando handler de signals...\n");//---Instalando sigint
    sa.sa_handler = sigint_handler;
    sa.sa_flags = 0; //SA_RESTART;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Error al instalar handler de SIGINT");
        exit(1);
    }
    printf("Handler de SIGINT instalado\n");


    printf("\nAccediendo a FIFO : %s ...\n", FIFO_NAME);//---Instalando FIFO
    if(mknod(FIFO_NAME, S_IFIFO | 0666, 0) != 0) {
        if(errno == EEXIST)
            printf("Ya existe el archivo [myfifo]\n");
        else {
            perror("Error al crear la FIFO");
            return E_MKNOD;
        }
    }
    else
        printf("Archivo [myfifo] creado por [reader]\n");



	printf("\nEsperando ejecución del programa [writer]\n");
	fd = open(FIFO_NAME, O_RDONLY);//--- Abriendo FIFO
    if(fd == -1)
    {
        perror("Error al abrir la FIFO. Saliendo\n");
        return E_OPEN_FIFO;
    }
	printf("Programa [writer] conectado. \n");




    fprintf(stdout, "\nAbriendo archivo %s\n", ARCHIVO_SIGN);
	fdSign = fopen(ARCHIVO_SIGN, "a+t");//---Abriendo archivo SIGN
    if(fdSign == NULL)
    {
        perror("Error al abrir archivo de señales\n");
        close(fd);
        return E_OPEN_SIGN;
    }
    printf("Archivo %s creado\n", ARCHIVO_SIGN);



    fprintf(stdout, "\nAbriendo archivo %s\n", ARCHIVO_LOG);
	fdLog = fopen(ARCHIVO_LOG, "a+t");//---Abriendo archivo LOG
    if(fdLog == NULL)
    {
        perror("Error al abrir archivo de log\n");

        fclose(fdSign);
        close(fd);

        return E_OPEN_LOG;
    }
    printf("Archivo %s creado\n", ARCHIVO_LOG);
    printf("... \n\n\n");


    printf("Recibiendo mensajes desde [writer]:\n\n");
	do  //LOOP
	{
		if ((n = read(fd, cad, 300)) == -1) {
			perror("FIFO no leida");
            printf("Cierrando archivos de texto y fifo\n");
            fclose(fdLog);
            fclose(fdSign);
            close(fd);
            return E_READ_FIFO;


        }
		else if (n > 0) //---pregunta por EOF
		{


			cad[n] = '\0';// + NULL

            strcpy(cad_bis, cad);
            strtok(cad_bis, ":");


            if(!strcmp(cad_bis, "DATA")) {
                printf("Datos recibidos por FIFO:");
                fprintf (fdLog, "%s\n", cad);
            }
            else if(!strcmp(cad_bis, "SIGN")) {
                printf("Señal recibida por FIFO:");
                fprintf (fdSign, "%s\n", cad);
            }
            else {
                printf("Datos sin formato recibidos por FIFO:");

            }

            printf("%d bytes leidos: \"%s\"\n", n, cad);

		}
        else {
            perror("\nError al leer la FIFO");
            printf("Cerrando archivos de texto y FIFO\n");
            fclose(fdLog);
            fclose(fdSign);
            close(fd);
            return E_WRITER_CERRADO;
        }
	}

	while (n > 0);

    printf("Saliendo del programa [reader]...\n");
    printf("Cerrando archivos de texto y FIFO\n");

    fclose(fdLog);
    fclose(fdSign);
    close(fd);

	return 0;
}//FIN MAIN
