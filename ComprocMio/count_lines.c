#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void error_exit(char* msg, int exstatus) {
    perror(msg);
    exit(exstatus);
}

int main(int argc, char** argv) {
    if (argc != 3) {
        error_exit("Usage: ./count_lines <parameter1> <2param>\n",1);
    }

    int cat2grep[2];
    int grep2wc[2];

    if (pipe(cat2grep) < 0) error_exit("error pipe\n",1);
    if (pipe(grep2wc) < 0) error_exit("error pipe\n",1);

    int pid1 = fork();
    if (pid1 == -1) error_exit("error fork\n",1);
    else if (pid1 == 0) {
        dup2(cat2grep[1],1);
        close(cat2grep[0]);
        close(cat2grep[1]);
        close (grep2wc[0]);
        close (grep2wc[1]);
        execlp("cat", "cat", argv[1], (char*)NULL);
        error_exit("error execlp\n",1);
    }

    int pid2 = fork();
    if (pid2 == -1) error_exit("eror fk\n",1);
    else if (pid2 == 0) {
        dup2(cat2grep[0],0);
        close (cat2grep[0]);
        close (cat2grep[1]);
        dup2(grep2wc[1],1);
        close (grep2wc[0]);
        close (grep2wc[1]);
        execlp("grep", "grep", argv[2], (char*)NULL);
        error_exit("error exec\n",1);
    }

    int pid3 = fork();
    if (pid3 == -1) error_exit("e f\n",1);
    else if (pid3 == 0) {
        dup2(grep2wc[0],0);
        close(grep2wc[1]);
        close(grep2wc[0]);
        close(cat2grep[1]);
        close(cat2grep[0]);
        execlp("wc", "wc", "-l", (char*)NULL);
        error_exit("errorrr execlp\n",1);
    }

    close(grep2wc[1]);
    close(grep2wc[0]);
    close(cat2grep[1]);
    close(cat2grep[0]);
    while(waitpid(-1,NULL,0) > 0);
}
