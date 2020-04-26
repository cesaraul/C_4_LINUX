 #include <stdio.h> 
 #include <stdlib.h> 
 #include <errno.h> 
 #include <unistd.h>
 // para que se tenga bidireccionalidad lo ideal es tener 2 pipes

int main(void) {

int pfds[2];  // array para el file descriptor
char buf[30];

pipe(pfds);

 if (!fork()) {

    printf(" CHILD: writing to the pipe\n");
    close(pfds[0]);//es importante cerrar para que no sea el mismo hijo quien lea el archivo 
    write(pfds[1], "test", 5); // escribe en el pipe 
    printf(" CHILD: exiting\n");
    exit(0);

} else {

    printf("PARENT: reading from pipe\n");
    close(pfds[1]);// es importante cerrrar para que el padre no escriba y lea
    read(pfds[0], buf, 5); // lee del pipe el mensaje cargado
    printf("PARENT: read \"%s\"\n", buf); 
    wait(NULL);
}
return 0;