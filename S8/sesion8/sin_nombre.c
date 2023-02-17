#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void error_n_exit(char * msg, int exstatus) {
    perror(msg);
    exit(exstatus);
}


int main(int argc, char * argv[]) {
    char buff[16];
    int fd[2];

    if (pipe(fd) == -1) error_n_exit("error on pipe", 1);

    int pid = fork();

    if (pid == -1) error_n_exit("error on fork", 1);
    // child
    else if (pid == 0) {
        dup2(fd[0],0); // reading
        close(fd[1]);
        // muta a cat
        execlp("cat", "cat", (char *) NULL);
        error_n_exit("error on execlp",1);
    }
    // parent
    else {
        close(fd[0]);
        sprintf(buff,"Inicio\n");
        write(fd[1], buff, strlen(buff));
        close(fd[1]); // Do not close for question 68
        // wait for child
        if (waitpid(-1,NULL,0) == -1) error_n_exit("error on waitpid",1);
        sprintf(buff, "Fin\n");
        write(1,buff,strlen(buff));
    }
}
