#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char** argv) {
    if (argc != 4) {
        perror("Usage : 3 ARGS VOLUDO \n");
        exit(1);
    }

    int ini = atoi(argv[2]);
    int fi = atoi(argv[3]);

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) exit(EXIT_FAILURE);
    int file_size = lseek(fd,0,SEEK_END);
    if (ini < 0 || ini > file_size || fi < 0 || fi > file_size) {
        perror("Invalid sizes (max size 26 min 0)\n");
        exit(EXIT_FAILURE);
    }

    int whatread = fi-ini;
    char buff[fi-ini+1];
    lseek(fd,3,SEEK_SET);
    int r = read(fd, &buff, fi-ini+1);
    write(1,&buff,r);
    printf("\n");
}
