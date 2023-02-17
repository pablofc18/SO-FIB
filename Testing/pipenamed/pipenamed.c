#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char** argv) {

    if (mknod("mipipa", S_IFIFO|0600, 0) < 0 && errno != EEXIST) {
        perror ("Error pipa mknod\n");
        exit(EXIT_FAILURE);
    }


    //int fdW = open("mipipa", O_WRONLY);

    int pid = fork();
    if (pid == -1) exit(69);
    else if (pid == 0) {
    	int fd = open("mipipa", O_WRONLY);
        dup2(fd,69);
        close(fd);
        execlp("./mmm", "./mmm", (char*)NULL);
        exit(1);
    }

	int fd = open("mipipa", O_RDONLY);
    int r;
    char buff[64];
    while ((r = read(fd,&buff,strlen(buff))) > 0) {
        write(1,&buff,r);
    }

    close (fd);
    //close (fdW);

    while (waitpid(-1,NULL,0) > 0);
}
