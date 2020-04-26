//
//  main.c
//  clase1_C
//
//  Created by Cesar Cruz on 4/2/20.
//  Copyright © 2020 Cesar Cruz. All rights reserved.
//

#include <stdio.h>

int suma_res(int x,int y,char op) //función de operaciones
    {
        int resultado=0;
        switch (op){
        case 'S':
            resultado=x+y;
            break;
        case 'R':
            resultado=x-y;
             break;
        default:
            resultado=0;
            break;   }
    return resultado;
    }
int main() {
    int a=1,b=5,resultado=0;
    char operador='S';
    resultado= suma_res(a,b,operador);
    printf("El resultado es: %d",resultado);
    return 0;
}
