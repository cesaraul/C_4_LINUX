#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>//

/*Agregamos un handler para recibir la señal del hijo sin necesidad de interrumpir
la rutina de padre, notese que no es necesario poner la configuración sigaction dentro del while true
*/
void hand_child(int sig) // esto es lo que se ejecuta cuando llega la señal
{   //write(1,,) el uno es porque estamos escribiendo en el standart output
	write(1,"llego sigchild!!\n",18);
	wait(NULL);
}
int main(void)
{
	pid_t pid; //definición de la variable

	struct sigaction sa;
	sa.sa_handler = hand_child;  
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);

	switch(pid = fork()) // pide hacer el fork- creo un proceso igual apartir de esta linea
	{      //pid recibe el id del proceso
		case -1:
		perror("fork"); /* something went wrong */
		exit(1);
		break;

		/* parent exits */
		case 0: // el fork en el hijo siempre devuelve 0 osea pid==0
		printf(" CHILD: This is the child process!\n");
		printf(" CHILD: My PID is %d\n", getpid());
		printf(" CHILD: My parent's PID is %d\n", getppid());
		printf(" CHILD: Enter my exit status (make it small): ");
		sleep(5);
		printf(" CHILD: I'm outta here!\n");
		exit(0);//similar a return, devuelve el rv (el numero que ingresamos)
		break;


		default://aqui es donde viene en el caso del padre
		if (sigaction(SIGCHLD,&sa,NULL)==-1) // configurar para SIGCHLD la estructura sa
    	{
        	perror("sigaction");
        	exit(1);
    	}
		printf("PARENT: This is the parent process!\n");
		printf("PARENT: My PID is %d\n", getpid());
		printf("PARENT: My childs PID is %d\n", pid);
		while (1)
		{
			printf("trabajando...\n");
			sleep(1);
		}
		
		printf("PARENT: I'm outta here!\n");
	}
}
