#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void error_exit(char* msg, int es) {
    perror(msg);
    exit(es);
}

void f_sigusr1(int s) {
    printf("%d: USR1 received\n", getpid());
    exit(0);
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: ./prog1 <1arg>\n");
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[1]);
    int *pids = malloc(n*sizeof(int));
    int i;
    for (i = 0; i < n; ++i) {
        pids[i] = fork();
        if (pids[i] == -1) error_exit("error fork\n",1);
        else if (pids[i] == 0) {
            printf("hijo num:%d\n",i);

            sigset_t mask;
            sigfillset(&mask);
            sigprocmask(SIG_BLOCK,&mask,NULL);

            struct sigaction sa;
            sa.sa_handler = &f_sigusr1;
            sa.sa_flags = 0;
            sigfillset(&sa.sa_mask);
            if (sigaction(SIGUSR1,&sa,NULL) < 0) error_exit("error sigaction\n",1);
            sigfillset(&mask);
            sigdelset(&mask,SIGUSR1);
            sigsuspend(&mask);
        }
    }

    char ch;
    while (read(0,&ch,1) > 0);
    printf("Parent has created all childs\n");
    for (i = 0; i < n; ++i) {
        kill(pids[i],SIGUSR1);
    }

    //libera hijos y muere
    while (waitpid(-1,NULL,0) > 0);

}
