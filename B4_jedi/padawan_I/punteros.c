#include <stdio.h>

void dublicar (int * a) // recibe un puntero es decir una dirección de memoria &valor

{
    *a*=2;  // se modifica el valor de la dirección de memoria a es un puntero 
}


int main()

{



  //------------parte 1 punteros  
    int number=0;
    int *poinToNumber=&number;
        // dirección de memoria y contenido de la dirección de memoria 
    printf("%p , %d\n",poinToNumber,*poinToNumber);


   //------------parte 2 punteros

    int a=5;
    printf("Antes de duplicar a= %d \n",a);
    dublicar(&a);
    printf("despued de duplicar a= %d\n",a);
    

}