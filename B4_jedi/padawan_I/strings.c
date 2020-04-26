#include <stdio.h>
#include <string.h>
int main(){

    char * text = "cesar";  
    char * text1 = "cruz"; 
    //comparación en linea si el valor de == 0 es verdadero toma el primero sino toma el segundo
    printf("El texto es %s \n",strcmp(text,text1)==0 ? "igual" : "diferente");   

return 0;    
    }
     
