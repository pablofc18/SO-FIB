#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char** argv) {
    int fdpipe[2];
    int pid;

    if (pipe(fdpipe) < 0) exit(EXIT_FAILURE);

    pid = fork();
    if (pid == -1) exit(EXIT_FAILURE);
    else if (pid == 0) {
        //dup2(fdpipe[0],0);
        close(fdpipe[1]);
        int r;
        int num;
        while ((r = read(fdpipe[0],&num,sizeof(int))) > 0) {
            char buff[8];
            int numero = num + 1;
            sprintf(buff,"%d",numero);
            write(1,buff,strlen(buff));
            printf("\n");
        }
        close(fdpipe[0]);
    }
    else {
        int fd = open("numeros.bin", O_RDONLY);
        if (fd == -1) exit(EXIT_FAILURE);

        int r;
        int num;
        close(fdpipe[0]);
        int sz = lseek(fd, -sizeof(int), SEEK_END);
        //int i = 1;
        while(/*i != 4 && */ sz >= 0 && (r = read(fd,&num,sizeof(int))) > 0) {
            //dup2(fdpipe[1],1);
            //close(fdpipe[1]);
            write(fdpipe[1], &num, sizeof(int));
            //++i;
            sz = lseek(fd, sz-sizeof(int), SEEK_SET);
            //if (sz < 0) break;
        }
        close(fdpipe[1]);
    }

    while(waitpid(-1,NULL,0) > 0);
}
