#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char * argv[]) {
    if (argc != 3) {
        printf("Usage: ./insertar2x <name_file> <position>\n");
        exit(1);
    }

    int fd = open(argv[1], O_CREAT|O_RDWR);
    if (fd == -1) {
        perror("Error open\n");
        exit(1);
    }

    int pos = atoi(argv[2]);

    int size_file = lseek(fd,-1,SEEK_END);

    char buff[8];
    sprintf(buff, "X");
    char buff2[8];
    for (int i = pos; i < size_file+1; ++i) {
        // copiar char (1ª iteracion poner X) pegar after 1 byte
        lseek(fd,i,SEEK_SET);
        read(fd,&buff2,1);
        lseek(fd,i,SEEK_SET);
        write(fd,&buff,1);
        sprintf(buff, "%s", buff2);
    }
    lseek(fd,0,SEEK_END);
    write(fd,&buff,1);

    close(fd);
}
