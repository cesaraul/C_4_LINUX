#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>//

void hand(int sig) // esto es lo que se ejecuta cuando llega la señal
{
	write(1,"se presiono ctrl+c!!\n",21);// la señal recibida es ctrl+c SIGINT
    //WRITE Es de mas bajo nivel que printf debo indicar la cantidad de bytes que 
    //tambien sale por el standart output
}

int main(void)
{   char s[200];
	struct sigaction sa;// structura sigaction

	sa.sa_handler = hand; // hand es el nombre de la funcion
	sa.sa_flags = 0; //SA_RESTART; //0;// este flag cambia el comportamiento de las sigcalls
	sigemptyset(&sa.sa_mask);// pongo la mascara en cero usando emtyset

	if (sigaction(SIGINT,&sa,NULL)==-1) // configurar para SIGINT la estructura sa
    {
        perror("sigaction");
        exit(1);
    }
       
    /*
     //=========EJEMPLO 1 para test de reaccion de syscall fgets frente a flags	
	printf("Enter a String:\n");
	   
	if(fgets(s,sizeof(s),stdin) == NULL)// con stdin estoy leyendo del standart input en vz de una archivo
	{  // se almacena en S, y con el sizeof restrinjo que lo maximo que almanece sea te ese tamaño
		perror("error en fgets\n");
	}
	else
	{
		printf("ingresaste:%s\n",s);// imprime lo que ingresaste
	}
*/


     //=========EJEMPLO 2 para test de reaccion de syscall sleep frente a flags 0 o SA_RESTART
     
     while(1)
    {
		printf("inicio:\n"); 
	    sleep(30);
	    printf("fin:\n");
	}


	return 0;
}
