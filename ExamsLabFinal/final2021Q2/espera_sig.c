#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void error_exit(char * msg, int status) {
    perror(msg);
    exit(status);
}

void sig_usr_int(int s) {
    char buff[64];
    if (s == SIGINT) {
        sprintf(buff, "Signal SIGINT received\n");
        write(2,buff,strlen(buff));
        exit(1);
    }
    else if (s == SIGUSR1) {
        sprintf(buff, "Signal SIGUSR1 received\n");
        write(2,buff,strlen(buff));
        exit(2);
    }
    else if (s == SIGUSR2) {
        sprintf(buff, "Signal SIGUSR2 received\n");
        write(2,buff,strlen(buff));
        exit(3);
    }
}

int main(int argc, char * argv[]) {
   char buff[64];

   struct sigaction sa;
   sigset_t mask;
   sigfillset(&mask);
   sigprocmask(SIG_BLOCK, &mask, NULL);

   // mod sigs:int,usr1,usr2
   sa.sa_handler = &sig_usr_int;
   sa.sa_flags = 0;
   sigfillset(&sa.sa_mask);
   if (sigaction(SIGINT, &sa, NULL) < 0) error_exit("sigaction", 1);
   if (sigaction(SIGUSR1, &sa, NULL) < 0) error_exit("sigusr1", 1);
   if (sigaction(SIGUSR2, &sa, NULL) < 0) error_exit("sigusr2", 1);

   // espera pasiva
   sigfillset(&mask);
   sigdelset(&mask,SIGINT);
   sigdelset(&mask,SIGUSR1);
   sigdelset(&mask,SIGUSR2);
   sigsuspend(&mask);


}
