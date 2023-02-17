#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv) {
    // abrir named pipe ya creada!!
    int fdnamedpipe = open("MIPIPE", O_RDONLY);
    if (fdnamedpipe == -1) {
        perror("error open named pipe\n");
        exit(EXIT_FAILURE);
    }

    int pid = fork();
    if (pid == -1) {
        perror("error fork\n");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        dup2(fdnamedpipe,0);
        close(fdnamedpipe);

        // muta a wc -l
        execlp("wc", "wc", "-c", (char*)NULL);
        perror("error execlp\n");
        exit(EXIT_FAILURE);
    }

    close(fdnamedpipe);
    while(waitpid(-1,NULL,0)>0);
}
