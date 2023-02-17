#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void f_sigalrmusr1(int s) {
    char buff[64];
    if (s == SIGUSR1) {
        sprintf(buff, "%d: SIGUSR1 received\n", getpid());
        write(1,buff,strlen(buff));
    }
    if (s == SIGALRM) {
        sprintf(buff, "%d: TIMEOUT\n", getpid());
        write(1,buff,strlen(buff));
    }
}

int main(void) {
    struct sigaction sa;
    sigset_t mask;

    sigfillset(&mask);
    sigprocmask(SIG_BLOCK,&mask,NULL);

    sa.sa_flags = 0;
    sa.sa_handler = &f_sigalrmusr1;
    sigfillset(&sa.sa_mask);
    if (sigaction(SIGALRM,&sa,NULL) < 0) exit(EXIT_FAILURE);
    if (sigaction(SIGUSR1,&sa,NULL) < 0) exit(EXIT_FAILURE);

    sigfillset(&mask);
    sigdelset(&mask, SIGUSR1);
    sigdelset(&mask, SIGALRM);
    alarm(5);
    sigsuspend(&mask);


}
