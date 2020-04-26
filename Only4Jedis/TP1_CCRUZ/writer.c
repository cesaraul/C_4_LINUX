
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#define FIFO_NAME "myfifo"
///ERRORES
#define E_MKNOD             -1
#define E_OPEN_FIFO         -2
#define E_FGETS             -3
#define E_READER_CERRADO    -4
#define E_ESCRIBIR_SIGUSR1  -5
#define E_ESCRIBIR_SIGUSR2  -6
#define E_ESCRIBIR_FIFO     -7
#define E_SIGINT            -8

volatile sig_atomic_t fd;

char cadenaSIGUSR1[10];
char cadenaSIGUSR2[10];


void sigint_handler(int sig)
{
    write(0, "\nPrograma [writer] cerradp... \n", sizeof("\nPrograma [writer] cerradp... \n"));
    close(fd);
    exit(E_SIGINT);
}


void sigpipe_handler(int sig)
{
    write(0, "\nPrograma [reader] cerrado...\n", sizeof("\nPrograma [reader] cerrado...\n"));
    close(fd);
    exit(E_READER_CERRADO);
}

void sigusr1_handler(int sig)
{
    int n;

    if ((n = write(fd, cadenaSIGUSR1, strlen(cadenaSIGUSR1)+1)) == -1) {
			perror("Error al escribir en la FIFO.");
            exit(E_ESCRIBIR_SIGUSR1);
    }
	else {
        write(0, "\nSe ha recibido SIGUSR1. Enviando a reader\n", sizeof("\nSe ha recibido SIGUSR1. Enviando a reader\n"));
        write(0, "Ingrese texto o senal SIGUSR1 o SIGUSR2 para enviar a reader: ", sizeof("Ingrese texto o senal SIGUSR1 o SIGUSR2 para enviar a reader: "));
    }
    return;
}

void sigusr2_handler(int sig)
{
    int n;

    if ((n = write(fd, cadenaSIGUSR2, strlen(cadenaSIGUSR2)+1)) == -1) {
			perror("Error al escribir en la FIFO.");
            exit(E_ESCRIBIR_SIGUSR2);
    }
	else {
        write(0, "\nSe ha recibido SIGUSR2. Enviando a reader\n", sizeof("\nSe ha recibido SIGUSR2. Enviando a reader\n"));
        write(0, "Ingrese texto o senal SIGUSR1 o SIGUSR2 para enviar a reader: ", sizeof("Ingrese texto o senal SIGUSR1 o SIGUSR2 para enviar a reader: "));
    }
    return;
}

int main(void)
{
  pid_t miPID;
	  char cad[300]; //---Cadenas
    char*cad_bis;
    char cad_dat[300];
	  int n;

    struct sigaction sa;
    struct sigaction si;
    struct sigaction sa_sigusr1;
    struct sigaction sa_sigusr2;

    printf("Sistemas Operativos de Proposito General\n");
    printf("TP1 programa [writer]\n\n");

    miPID = getpid(); //pid del proceso
    printf("PID de serialService : %d\n\n", miPID);

///-----------INSTALANDO HANDLERS

    printf("Instalando handlers de señales...\n");
    si.sa_handler = sigint_handler;
    si.sa_flags = 0;
    sigemptyset(&si.sa_mask);
    if (sigaction(SIGINT, &si, NULL) == -1) {
        perror("Error instalando handler de SIGINT");
        exit(1);
    }
    printf("Handler de SIGINT instalado\n");

    sa.sa_handler = sigpipe_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGPIPE, &sa, NULL) == -1) {
        perror("Error al instalar handler de SIGPIPE");
        exit(1);
    }
    printf("Handler de SIGPIPE instalado\n");

    sa_sigusr1.sa_handler = sigusr1_handler;
    sa_sigusr1.sa_flags = SA_RESTART;
    sigemptyset(&sa_sigusr1.sa_mask);
    if (sigaction(SIGUSR1, &sa_sigusr1, NULL) == -1) {
        perror("Error al instalar handler de SIGUSR1");
        exit(1);
    }
    printf("Handler de SIGUSR1 instalado\n");
    sa_sigusr2.sa_handler = sigusr2_handler;
    sa_sigusr2.sa_flags = SA_RESTART;
    sigemptyset(&sa_sigusr2.sa_mask);

    if (sigaction(SIGUSR2, &sa_sigusr2, NULL) == -1) {
        perror("Error al instalar handler de SIGUSR2");
        exit(1);
    }
        printf("Handler de SIGUSR2 instalado\n");

        printf("\nAccediendo a FIFO : %s ...\n", FIFO_NAME);
        if(mknod(FIFO_NAME, S_IFIFO | 0666, 0) != 0) {


          if(errno == EEXIST)
            printf("Ya existe un archivo [myfifo]\n\n");
            else {
            perror("Error al crear la FIFO");
            return E_MKNOD;
        }
    }
    else
        printf("Archivo [myfifo] creado por writer\n\n");

	printf("Esperando ejecución [reader]...\n");
	fd = open(FIFO_NAME, O_WRONLY);

    if(fd == -1)
    {
        perror("Error al abrir FIFO. Saliendo...\n");
        return E_OPEN_FIFO;
    }
    sprintf(cadenaSIGUSR1, "%s%s%s", "SIGN", ":", "1");
    sprintf(cadenaSIGUSR2, "%s%s%s", "SIGN", ":", "2");

	printf("Programa <<reader>> conectado\n");
    printf("------------------------------ \n\n\n");
	while (1) ////--------LOOP
	{
        printf("Ingrese texto o senal SIGUSR1 o SIGUSR2 para enviar a [reader]: ");
		cad_bis = fgets(cad, 300, stdin);

        cad_bis [strcspn(cad_bis, "\n")] = '\0';

        if(cad_bis != cad) {
            perror("Error al leer buffer stdin...\n");
            close(fd);
            return E_FGETS;
        }

        sprintf(cad_dat, "%s%s%s", "DATA", ":", cad_bis);

		if ((n = write(fd, cad_dat, strlen(cad_dat))) == -1) {
			perror("Error al escribir en la FIFO.");
            return E_ESCRIBIR_FIFO;

        }
		else
			printf("Se escribieron %d bytes\n", n);
	}
	return 0;
}
