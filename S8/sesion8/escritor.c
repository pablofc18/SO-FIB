#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define MAXBUFF 16

void error_n_exit(char * msg, int status) {
    perror(msg);
    exit(status);
}

int main() {
    char buff[MAXBUFF];

    if (mknod("pipe1", S_IFIFO|0600, 0) < 0 && (errno != EEXIST)) {
        error_n_exit("error mknod", 1);
    }

    int fd = open("pipe1", O_WRONLY);

	printf("***%d***\n",fd);

    //char ch;
    int r;
    while ((r = read(0, &buff, MAXBUFF)) > 0) {
        write(fd,&buff,r);
    }

    close(fd);
}
