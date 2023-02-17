#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Error tolai son 2(+1) args\n");
        exit(1);
    }

    if (mknod(argv[1], S_IFIFO|0666, 0) < 0 && errno != EEXIST) {
        perror ("error mknod pipe\n");
        exit(EXIT_FAILURE);
    }

    //int fdpipe = open("mypipe", O_)

    int n = atoi(argv[2]);
    for (int i = 0; i < n; ++i) {
        int pid = fork();
        if (pid == -1) exit(EXIT_FAILURE);
        else if (pid == 0) {
            //close(1);
            int fdpipe = open(argv[1], O_WRONLY);
            if (fdpipe == -1) exit(EXIT_FAILURE);
            dup2(fdpipe,1);
            // muta a aux
            char buff[4];
            sprintf(buff,"%d",i+1);
            execlp("./aux", "./aux", buff, (char*)NULL);
            exit(EXIT_FAILURE);
        }
    }

    // padre lee de la named pipe y escribe por std output text format
    int fdpipeparent = open(argv[1], O_RDONLY);
    if (fdpipeparent == -1) exit(EXIT_FAILURE);
    int r;
    char buff[64];
    while ((r = read(fdpipeparent, &buff, sizeof(buff))) > 0) {
        write(1,&buff,r);
    }
    close (fdpipeparent);

    int stat;
    while (waitpid(-1,&stat,0) > 0) {
        if (WIFEXITED(stat)) {
            printf("ok wifexited: %d\n", WEXITSTATUS(stat));
        }
        else if (WIFSIGNALED(stat)) {
            printf("signal pana: %d\n", WTERMSIG(stat));
        }
    }
}
