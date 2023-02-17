#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int fd = open(argv[1], O_WRONLY|O_CREAT|O_TRUNC,S_IRWXU);
    if (fd == -1) exit(EXIT_FAILURE);

    int num = 14;
    write(fd,&num,sizeof(int));
    int numer = 18;
    lseek(fd,sizeof(int),SEEK_SET);
    write(fd,&numer,sizeof(int));
	numer = 23;
    lseek(fd,2*sizeof(int),SEEK_SET);
    write(fd,&numer,sizeof(int));
    close(fd);
}
