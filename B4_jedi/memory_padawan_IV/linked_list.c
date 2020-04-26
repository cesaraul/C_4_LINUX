#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int number;
    struct Node * next;  // estructura autoreferenciada

}Node;
