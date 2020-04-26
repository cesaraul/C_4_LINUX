
#include <stdio.h>
#include "mylib.h" // comillas porque no es una libreria estandas y la busca en el propio direcotorio

void hello(const char * name)
{
    printf("Hola %s\n",name);
}