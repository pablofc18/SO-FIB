#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
    if (argc != 2) exit(EXIT_FAILURE);

    int num = 1000;
    int num2 = 18;

    int fd = open(argv[1], O_CREAT|O_WRONLY|O_TRUNC, 0600);
    if (fd == -1) exit(EXIT_FAILURE);

    write(fd,&num,sizeof(int));
    lseek(fd,sizeof(int),SEEK_SET);
    write(fd,&num2,sizeof(int));

    close (fd);
}
