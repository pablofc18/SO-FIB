#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
    if (argc != 5) {
        perror("Usage: ./enkripta <name file> <name_file> <num1> <num2>\n");
        exit(EXIT_FAILURE);
    }

    if (mknod(argv[1], S_IFIFO|0600, 0) < 0 && errno != EEXIST) {
        perror("error mknod\n");
        exit(EXIT_FAILURE);
    }

    if (mknod(argv[2], S_IFIFO|0600, 0) < 0 && errno != EEXIST) {
        perror("error mknod\n");
        exit(EXIT_FAILURE);
    }

    char buff[64];
    int pid;
    pid = fork();
    if (pid == -1) {
        perror("error mknod\n");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        // abrir pipe de lectuar (primera pipe)
        int fdpipeL = open(argv[1], O_RDONLY);
        if (fdpipeL == -1) exit(EXIT_FAILURE);
        int r;
        int fd = open("n.txt", O_WRONLY|O_CREAT, 0600);
        while((r = read(fdpipeL,&buff,sizeof(buff))) > 0) {
            //int numbytes = r - atoi(argv[3]);
            //
            //sprintf(buff, "%d", numbytes);
            //
            write(fd,&buff,strlen(buff));
        }
        close (fdpipeL);
        close (fd);
		exit(0);
    }

    int pid2;
    pid2 = fork();
    if (pid2 == -1) {
        perror("error mknod\n");
        exit(EXIT_FAILURE);
    }
    else if (pid2 == 0) {
       // abrir segunda pipe esdcribir
       int fdpipeW = open(argv[2], O_WRONLY);
       if (fdpipeW == -1) exit(EXIT_FAILURE);

       int r;
       char buff2[64];
       while ((r = read(0, &buff2, sizeof(buff2))) > 0) {
           int numbytes = r + atoi(argv[4]);
           sprintf(buff2, "%d", numbytes);
           write(fdpipeW, &buff2, strlen(buff));
       }
       close (fdpipeW);
	   exit(0);
    }

    //close (fdpipe)
    while(waitpid(-1,NULL,0) > 0);
}
