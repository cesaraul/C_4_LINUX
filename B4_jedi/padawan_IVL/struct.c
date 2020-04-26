#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc,const char * argv[])
{

    struct 
    {
        char name[100];
        int age;
    }person;

    if(argc < 3)
    {
        printf("Indique nombre y edad por favor\n");
        return 1; //codigo de error
    }

    if(strlen(argv[1])<100)
    {
        strcpy(person.name,argv[1]);
    }
    
    person.age= atoi(argv[2]); // atou¡i es parte de stdlib string a numero

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