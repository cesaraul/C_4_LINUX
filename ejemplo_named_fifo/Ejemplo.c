 /*===WRITER===*/


 #define FIFO_NAME "myfifo" // definimos el nombre de la cola
 
 int main(void)
{
char s[100]; 
int bytesWrote, fd;


if (mknod(FIFO_NAME, S_IFIFO | 0666, 0)<-1)//creamos la cola tipo FIFO ESPECIAL
    {
        perror("mknod!!");
    }

printf("waiting for readers...\n");

// se queda parado aqui hasta tener un lector
fd = open(FIFO_NAME, O_WRONLY); // abrimos el archivo que acabamos de crear lo abrimos solo modo lectura

printf("got a reader--type some stuff\n");

while (1) {
    fgets(s,BUFFER_SIZE,stdin);
if ((bytesWrote = write(fd, s, strlen(s))) == -1)
{
    perror("write"); 
}
else
{
    printf("writer: wrote %d bytes\n", bytesWrote);
}
     }