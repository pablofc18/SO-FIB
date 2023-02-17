#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void error_exit(char* msg, int exstatus) {
    perror(msg);
    exit(exstatus);
}

int main(int argc, char** argv) {
    if (argc != 2) {
        error_exit("Usage: ./add_integers <file_name>\n",1);
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) error_exit("error open\n",1);

    int r;
    int num;
    int sum = 0;
    while((r = read(fd,&num,sizeof(int))) > 0) {
        sum += num;
    }
    close(fd);

    int fdw = open("addition.txt", O_WRONLY|O_CREAT|O_TRUNC, 0600);
    if (fdw == -1) error_exit("error openn\n",1);

    char buff[64];
    sprintf(buff,"%d",sum);
    write(1,&buff,strlen(buff));
    write(fdw,&buff,strlen(buff));

    close(fdw);
}
