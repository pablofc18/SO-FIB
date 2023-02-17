#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {

    int fd = creat("salida.txt", O_WRONLY|O_CREAT|O_TRUNC|0600);
    if (fd == -1) {
        perror("ERROR CREAT()\n");
        exit(1);
    }
    char buff[8];
    sprintf(buff,"ABCD");
    write(fd,buff,strlen(buff));

}
