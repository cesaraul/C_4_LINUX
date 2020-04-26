#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char NAME[100];
typedef char EMAIL[100];

typedef struct 
{
    NAME name;
    EMAIL email;
}CONTACT;

int main (int argc,const char * argv[])
{
    CONTACT * list = NULL; // creamos un arreglo, seria un constacto, la dirección de memoria del primero
    char buffer[100];
    int goOn,listSize = 0;
do
{
    
    printf("ingrese el nombre del nuevo contacto(0 para terminar):\n");
    scanf("%99s",buffer);// indico que como maximo 99 caracteres

    if(strcmp("0",buffer)!=0) // si es distinto de 0 se empieza
    {

  
        if(!list){ // si la lista esta vacia entonces...
        // recerbamos memoria para un elemento 
           list = malloc(sizeof(CONTACT));

         } else
         { // si ya tenia elemntos, toma los que habia y agranda
            //* es por
            list=realloc(list,sizeof(CONTACT)*(listSize+1)); // se incrementa + 1 porque inicia en 0
          }

        strcpy(list[listSize].name,buffer); // copio el valor del buffer a la memoria
    
        printf("ingrese el email de %s:\n",buffer); // recibo el segundo valor 
        scanf("%99s",buffer);

        strcpy(list[listSize].email,buffer); // lo copio a memoria en la zona de email

        goOn = 1;// se ejecuta la primera vez y luego le asigno 1 para que continue 

        listSize++;// incrementamos el tamaño de lista
        
    }else
    {
        goOn = 0;
    }
    

} while (goOn);

printf("\n Esta es tu lista de contactos:\n");
printf("Nombre\t\tEmail\n");

for ( int i = 0; i < listSize; i++)
{

    printf("%s\t\t%s \n",list[i].name,list[i].email);
}

free(list); // liberamos la memmoria 

return 0;

}
/*
~/Documents/Clases_C/clase1_C/memory(master*) » gcc contact_list.c -o contact_list                                                      cesarcruz@Cesars-MacBook-Pro-5
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
~/Documents/Clases_C/clase1_C/memory(master*) » ./contact_list                                                                          cesarcruz@Cesars-MacBook-Pro-5
ingrese el nombre del nuevo contacto(0 para terminar):
cesar
ingrese el email de cesar:
cesar@
ingrese el nombre del nuevo contacto(0 para terminar):
raul
ingrese el email de raul:
raul@
ingrese el nombre del nuevo contacto(0 para terminar):
0

 Esta es tu lista de contactos:
Nombre          Email
cesar           cesar@ 
raul            raul@
*/
