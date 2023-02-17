#include <signal.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: 1 arg hijomio\n");
        exit(EXIT_FAILURE);
    }

    // creamos named pipe
    if (mknod("MIPIPE", S_IFIFO|0600, 0) < 0 && errno != EEXIST) {
        perror("error mknod\n");
        exit(EXIT_FAILURE);
    }


    int pid = fork();
    if (pid == -1) {
        perror("error fork\n");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        int fdpipe = open("MIPIPE", O_WRONLY);
        if (fdpipe == -1) exit(EXIT_FAILURE);

        dup2(fdpipe,1);
        close(fdpipe);

        execlp("./nums", "./nums", (char*)NULL);
        perror("error execlp\n");
        exit(EXIT_FAILURE);
    }

    int pid2 = fork();
    if (pid2 == -1) {
        perror("error fork\n");
        exit(EXIT_FAILURE);
    }
    else if (pid2 == 0) {
        int fdpipe = open("MIPIPE", O_RDONLY);
        if (fdpipe == -1) exit(EXIT_FAILURE);

        dup2(fdpipe,0);
        close(fdpipe);

        int fd = open(argv[1], O_WRONLY|O_CREAT|O_TRUNC, 0600);
        if (fd == -1) exit(EXIT_FAILURE);
        dup2(fd,1);
        close(fd);

        execlp("sort", "sort", "-n", (char*)NULL);
        perror("error execlp\n");
        exit(EXIT_FAILURE);
    }

}
