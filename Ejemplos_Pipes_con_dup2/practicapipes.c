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
	pid_t pid; //definición de la variable pid
    int fds[2]; // creamos un file descriptor
    char buff[64]; // buffer para recibir el mensaje 
    int r; // variable para visualizar el retorno

	struct sigaction sa;
	sa.sa_handler = hand_child;  
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);

    //pipe(fds)
    if (pipe(fds) == -1) // creo el pipe y verifico el error 
    { // creo el pipe antes del fork para que lo compartan ambos
        perror("pipe"); 
        exit(1);
    }

	switch(pid = fork()) // pide hacer el fork- creo un proceso igual apartir de esta linea
	{      //pid recibe el id del proceso
		case -1:
			perror("fork"); /* something went wrong */
			exit(1);
		break;

		/* parent exits */
		case 0: // el fork en el hijo siempre devuelve 0 osea pid==0
        	close(fds[0]); // como buena practica y por seguridad cierro la lectura
		
        	printf(" CHILD: This is the child process!\n");
			printf(" CHILD: My PID is %d\n", getpid());
			printf(" CHILD: My parent's PID is %d\n", getppid());
			printf(" CHILD: Enter my exit status (make it small): ");
		
        //==========
        	sleep(5);        
        	write(fds[1],"hola!",6); // envio un mensaje
			sleep(10);
        //========
        	printf(" CHILD: I'm outta here!\n");
		
        	exit(0);//similar a return, devuelve el rv (el numero que ingresamos)
		break;


		default://aqui es donde viene en el caso del padre
        	close(fds[1]);// como buena preactica y precaución cierro la escritura

			if (sigaction(SIGCHLD,&sa,NULL)==-1) // configurar para SIGCHLD la estructura sa
    		{
        		perror("sigaction");
        		exit(1);
    		}
			printf("PARENT: This is the parent process!\n");
			printf("PARENT: My PID is %d\n", getpid());
			printf("PARENT: My childs PID is %d\n", pid);
			
		while (1)
		{   // r deberia valer 0 y el proceso hijo termina o 6 si recibe el mensaje 
            r = read(fds[0],buff,6);// se quedara aqui hasta que pueda leer el mensaje

            if (r>5)
            {
                printf("mensaje del hijo %s",buff);
            }
            

			printf("trabajando...\n");
			sleep(1);
		}
		
		printf("PARENT: I'm outta here!\n");
	}
}
