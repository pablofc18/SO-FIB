#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void fff(int s) {}

int main(int argc, char** argv) {
    /* char buff[64]; */
    /* sprintf(buff, "%d en hexa socio\n", getpid()); */
    /* write(1,&buff,strlen(buff)); */

    int fd = open("mypipe", O_WRONLY);
    char buff[64];
    sprintf(buff, "%d en hexa socio\n", getpid());
    write(fd,&buff,strlen(buff));

    sigset_t mask;
    sigfillset(&mask);
    sigprocmask(SIG_BLOCK,&mask,NULL);
    struct sigaction sa;
    sa.sa_flags = 0;
    sa.sa_handler = &fff;
    sigfillset(&sa.sa_mask);
    if (sigaction(SIGALRM, &sa, NULL) < 0) exit(EXIT_FAILURE);

    int n = atoi(argv[1]);
    sigfillset(&mask);
    sigdelset(&mask, SIGALRM);
    alarm(n);
    sigsuspend(&mask);
    // end
    exit(69);
}
