#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv) {
    if (argc != 2) exit(8567);

    int n = atoi(argv[1]);

    if (mknod("MIPIPE", S_IFIFO|0640, 0) < 0 && errno != EEXIST) {
        perror("ERRRROR\n");
        exit(EXIT_FAILURE);
    }

    int n_read = 0;


    int fd = open("salida.bin", O_WRONLY|O_CREAT|O_TRUNC, 0640);
    if (fd == -1) exit(777);

    for (int i = 0; i < n; ++i) {
        int pid = fork();
        if (pid == -1) exit(75);
        else if (pid == 0) {
            // 57 a pipe
            //close(fdpipeR);
            printf("sdsdfsdsd\n");
            int fdpipe = open("MIPIPE", O_WRONLY);
            if (fdpipe == -1) exit(EXIT_FAILURE);

            dup2(fdpipe,57);
            close(fdpipe);

            execlp("./aleatorios", "./aleatorios", "100", (char*)NULL);
            perror("hey bor\n");
            exit(1);
        }
        while(waitpid(pid,NULL,0) > 0);
    }

    int r;
    int num;
    //lseek(fd,0,SEEK_END);

    int fdpipeR = open("MIPIPE", O_RDONLY);
    if (fdpipeR == -1) exit(EXIT_FAILURE);
    printf("ksjhdaiaasaasasasasas\n");
    while((r = read(fdpipeR,&num,sizeof(int))) > 0) {
        //printf("asdasdrfsdfasdfasdf\n");
        write(fd,&num,r);
        lseek(fd,sizeof(int)*n_read,SEEK_SET);
        char buff[64];
        sprintf(buff, "%d", n_read);
        write(1,buff,strlen(buff));
        printf("\n");
        n_read += 1;
    }
    close(fdpipeR);

    int end = lseek(fd,0,SEEK_END);
    int mitad = end/2;
    mitad = lseek(fd,mitad,SEEK_SET);
    printf("%d",mitad);
    printf("\n");
    int number;
    read(fd,&number,sizeof(int));
    char buff2[16];
    sprintf(buff2,"Number: %d in pos: %d\n",number,mitad);
    write(1,buff2,strlen(buff2));


    //printf("eeeeee\n");
}
