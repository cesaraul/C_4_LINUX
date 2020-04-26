//
//  main.c
//  clase1_C
//
//  Created by Cesar Cruz on 4/2/20.
//  Copyright © 2020 Cesar Cruz. All rights reserved.
//=== si no entiendes nada de lo que esta debajo probablemente
//=== aun eres un padawan y es aqui donde empiezas

#include <stdio.h>

int main()
{

    int array[5];
    int i,count=5;

    for ( i = 0; i < count; i++)
    {
        array[i]=i*2;
    }

    for ( i = 0; i < count; i++)
    {
        printf("array[%d] = %d\n",i,array[i]);
    }
    
    return 0;
}