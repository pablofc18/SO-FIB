#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("salida.txt", O_RDWR);
    if (fd == -1) {
        perror("ERROR CREAT()\n");
        exit(1);
    }

    char buff[1];
    sprintf(buff,"X");
    // read last char and save it
    lseek(fd,-1,SEEK_END);
    char buff1[1];
    read(fd,buff1,sizeof(char));
    // move again position
    lseek(fd,-1,SEEK_END);
    // write X then last char
    write(fd,buff,sizeof(char));
    write(fd,buff1,sizeof(char));
}
