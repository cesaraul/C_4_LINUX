#include <stdio.h>

int main(){

    char * name = "cesar";  // coge la dirección de c
    int i;
    printf("Nombre =%s,(%p) \n",name,name);  //mostrara el valor del puntero y la dirección 
    for ( i = 0; i < 5; i++)
    {
        printf("name[%d](%p) = %c \n" ,i,name +i,* (name + i));
      //salida
      /*  Nombre =cesar,(0x10d1fbf8a) 
        name[0](0x10d1fbf8a) = c 
        name[1](0x10d1fbf8b) = e 
        name[2](0x10d1fbf8c) = s 
        name[3](0x10d1fbf8d) = a 
        name[4](0x10d1fbf8e) = r */
    }
     
    
}