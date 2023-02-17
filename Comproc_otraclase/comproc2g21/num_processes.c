#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

void error_exit(char *msg, int ex) {
    perror(msg);
    exit(ex);
}

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: ./name <1s arg> <2n arg>\n");
        exit(EXIT_FAILURE);
    }

    int ps2grep[2];
    int grep2wc[2];

    if (pipe(ps2grep) < 0) error_exit("error pipe\n",1);
    if (pipe(grep2wc) < 0) error_exit("error pipe\n",1);

    int pid = fork();
    if (pid == -1) error_exit("error fork\n",1);
    else if (pid == 0) {
        // muta a ps -a
        dup2(ps2grep[1],1);
        close(ps2grep[1]);
        close(ps2grep[0]);
        close(grep2wc[0]);
        close(grep2wc[1]);

        execlp("ps", "ps", "-aux", (char*)NULL);
        error_exit("Error execlp ps\n", 1);
    }

    pid = fork();
    if (pid == -1) error_exit("error fork\n",1);
    else if (pid == 0) {
        // muta a grep argv[1]
        dup2(ps2grep[0],0);
        close (ps2grep[0]);
        close (ps2grep[1]);

        dup2(grep2wc[1],1);
        close(grep2wc[1]);
        close(grep2wc[0]);

        execlp("grep", "grep", argv[1], (char*)NULL);
        error_exit("Error execlp ps\n", 1);
    }

    pid = fork();
    if (pid == -1) error_exit("error fork\n",1);
    else if (pid == 0) {
        //muta a wc -l
        int fdfile = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0666);
        if (fdfile == -1) error_exit("error open\n",1);

        dup2(grep2wc[0],0);
        dup2(fdfile,1);
        close(fdfile);
        close(grep2wc[0]);
        close(grep2wc[1]);
        close(ps2grep[0]);
        close(ps2grep[1]);

        execlp("wc", "wc", "-l", (char*)NULL);
        error_exit("error execlp wc\n",1);
    }

    close(grep2wc[0]);
    close(grep2wc[1]);
    close(ps2grep[0]);
    close(ps2grep[1]);

    while(waitpid(-1,NULL,0) > 0);

}
