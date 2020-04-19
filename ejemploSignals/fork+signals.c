#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*For permite crear un proceso desde otro proceso
*/
int main(void)
{
	pid_t pid; //definición de la variable
	int rv;
	int sarasa;
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
		scanf(" %d", &rv);
		printf(" CHILD: I'm outta here!\n");
		exit(rv);//similar a return, devuelve el rv (el numero que ingresamos)
		break;


		default://aqui es donde viene en el caso del padre
		printf("PARENT: This is the parent process!\n");
		printf("PARENT: My PID is %d\n", getpid());
		printf("PARENT: My childs PID is %d\n", pid);
		//con wait pasa a estado interruptible
		wait(&sarasa); /* el padre recibe el valor de retorno del hijo
		 se quedará aqui hasta que el hijo retorne el valor
		 si el padre no ejecuta wait el hijo queda zombie*/
		printf("PARENT: My child's exit status is: %d\n", WEXITSTATUS(sarasa));
		printf("PARENT: I'm outta here!\n");
	}
}
