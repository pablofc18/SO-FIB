#include <signal.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

void error_exit(char * msg, int status) {
    perror(msg);
    exit(status);
}


int main(int argc, char * argv[]) {
    char buff[64];
    if (argc != 2) {
        sprintf(buff, "Usage: ./n_espera_sig.c [NUM]\n");
        write(1, buff, strlen(buff));
        exit(1);
    }

    int n = atoi(argv[1]);
    int *pids;
    pids = malloc(n*sizeof(int));
    for (int i = 0; i < n; ++i) {
         pids[i] = fork();
        // child
        if (pids[i] == 0) {
            sprintf(buff, "My pid is: %d\n", getpid());
            write(1, buff, strlen(buff));
            // muta a espera_sig
            execlp("./espera_sig", "./espera_sig", (char*)NULL);
            error_exit("execlp\n", 1);
        }
    }

    // wait childs
    int status;
    int i;
    int fd = open("exit_status.int", O_WRONLY|O_CREAT|O_TRUNC, 0640);
    int p;
    while ((p = waitpid(-1,&status,0)) > 0) {
        if (WIFEXITED(status)) {
            for (i = 0; i < n; ++i) {
                if (pids[i] == p) {
                    lseek(fd,i*2*sizeof(int),SEEK_SET);
                    write(fd,&p,sizeof(int));
                    lseek(fd,i*2*sizeof(int)+sizeof(int), SEEK_SET);
                    int estatus = WEXITSTATUS(status);
                    write(fd,&estatus,sizeof(estatus)); // 1 byte due to estatus variable is only one digit
                }
            }
        }
    }

    free(pids);
	close (fd);
}
