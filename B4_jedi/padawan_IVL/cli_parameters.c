#include <stdio.h>

// argc es la cantidad de caracteres que recibe 

int main (int argc,char * argv[])

{

    for (int i = 0; i < argc; i++)
    {
        printf("Argumento %d = %s \n",i,argv[i]);

    }
    return 0;

}
/* --- salida
~/Documents/Clases_C/clase1_C(master*) » gcc cli_parameters.c -o cli_parameters                                                         cesarcruz@Cesars-MacBook-Pro-5
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
~/Documents/Clases_C/clase1_C(master*) » ./cli_parameters                                                                               cesarcruz@Cesars-MacBook-Pro-5
Argumento 0 = ./cli_parameters 
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
~/Documents/Clases_C/clase1_C(master*) » ./cli_parameters arg1 arg2                                                                     cesarcruz@Cesars-MacBook-Pro-5
Argumento 0 = ./cli_parameters 
Argumento 1 = arg1 
Argumento 2 = arg2 
*/