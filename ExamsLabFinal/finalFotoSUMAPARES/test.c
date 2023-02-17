#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    int fd = open(argv[1], O_CREAT|O_WRONLY, 0666);
    if (fd == -1) exit(EXIT_FAILURE);

    int num = 1;
    for (int i = 0; i < 100; ++i) {
        write(fd,&num,sizeof(int));
        lseek(fd,sizeof(int),SEEK_CUR);
    }
    close (fd);
}
