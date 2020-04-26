#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct PERSON
    {
        char name[100];
        int age;
    };

//recibe el struct por referencia
void fillPersonData(struct PERSON * person,const char * name, int age)
{
    if(strlen(name)<100)
    {
        strcpy((*person).name,name); // otra forma de escribir (*person).name es person->name 
    }
    (*person).age = age;
}

int main(int argc,const char * argv[])
{
    struct PERSON person; //person es de tipo struct PERSON , person es diferente al de la funcion fillpersondata por ello &person
   
    
    if(argc < 3)
    {
        printf("Indique nombre y edad por favor\n");
        return 1; //codigo de error
    }

    fillPersonData(&person,argv[1],atoi(argv[2])); // envia datos a la función dirección de memoria argv 1 y 2 de entrada por comando 


    printf("Name=%s,age=%d\n",person.name,person.age);



return 0;

}

/*Salida
gcc struct.c -o struct                                                                         cesarcruz@Cesars-MacBook-Pro-5
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
~/Documents/Clases_C/clase1_C(master*) » ./struct                                                                                       cesarcruz@Cesars-MacBook-Pro-5
Indique nombre y edad por favor
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
~/Documents/Clases_C/clase1_C(master*) » ./struct cesar 30                                                                          1 ↵ cesarcruz@Cesars-MacBook-Pro-5
Name=cesar,age=30*/