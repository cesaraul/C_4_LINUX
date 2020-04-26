#include <stdio.h>
#include <stdlib.h>

typedef struct {
  	uint32_t baudRate;
	char chStart;
	char chEnd;
	uint8_t msgMaxLen;
	
}uartManager_t;
static uartManager_t manager[3] = {0};

void uartManagerInit(int* handle)
{

 	manager[*handle].baudRate = 100;
	manager[*handle].chStart = 'c';
	manager[*handle].chEnd = 'r';
	manager[*handle].msgMaxLen = 6;

printf("%d\n",manager[*handle].baudRate);
printf("%c\n",manager[*handle].chStart);
printf("%c\n",manager[*handle].chEnd);
printf("%d\n",manager[*handle].msgMaxLen);

	
}

int main()

{
    int *handle;
    uartManagerInit(handle);
    
    return 0;
}