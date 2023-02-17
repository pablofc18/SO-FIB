#include <signal.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) {
    if (argc != 2) {
        perror("USAGE 1 ARGS\n");
        exit(EXIT_FAILURE);
    }

    sigset_t mask;
    sigfillset(&mask);
    sigprocmask(SIG_BLOCK, &mask, NULL);

    char buff[64];
    int n = atoi(argv[1]);
    int * pids = malloc(n*sizeof(int));
    for (int i = 0; i < n; ++i) {
        pids[i] = fork();
        if (pids[i] == -1) exit(EXIT_FAILURE);
        else if (pids[i] == 0) {
            execlp("./signal", "./signal", (char*)NULL);
            exit(EXIT_FAILURE);
        }
    }

    // send sigusr1 to all childs
    for (int i = 0; i < n; ++i) {
        kill(pids[i], SIGUSR1);
    }

    while (waitpid(-1,NULL,0) > 0);
}
