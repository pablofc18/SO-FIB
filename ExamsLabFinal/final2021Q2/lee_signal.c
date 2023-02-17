#include <sys/stat.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

void sig_alrm(int s) {}

int main(int argc, char * argv[]) {
    if (argc != 2) {
        printf("Usage: ./lee_signal <name_file> \n");
        exit(EXIT_FAILURE);
    }

    // reprogramar sigalarm
    struct sigaction sa;
    sa.sa_flags = 0;
    sa.sa_handler = &sig_alrm;
    sigfillset(&sa.sa_mask);
    if (sigaction(SIGALRM, &sa, NULL) < 0) exit(EXIT_FAILURE);


    if (mknod("mypipe", S_IFIFO|0644,0) < 0 && errno != EEXIST) {
        perror("ERROR pipe\n");
        exit(EXIT_FAILURE);
    }


    int fdpipe = open("mypipe", O_WRONLY);
    if (fdpipe == -1) {
       perror("Eror open\n");
       exit(1);
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("ERROR OPEN\n");
        exit(EXIT_FAILURE);
    }
    ////
    printf("****%d****\n", fd);
    printf("****%d****\n", fdpipe);
    ////

    int r;
    int num;
    int i = 0;
    char buff2[16];
    char buff3[64];
    while ((r = read(fd,&num,sizeof(int))) > 0) {
        int numero = num;
        char buff[16];
        sprintf(buff,"%d",numero);
        //write(1,&buff,strlen(buff));
        //printf("\n");

        // pasamos por la pipe: mypipe
        write(fdpipe,&num,sizeof(int));
        //write(fdpipe,&buff,strlen(buff)); // el numero leído
        //lseek(fdpipe,strlen(buff),SEEK_CUR);

        if (i%2 != 0) {
            sprintf(buff3, "El proceso %s ha terminado con %s\n", buff2, buff);
            write(1,buff3,strlen(buff3));
            //alarm(5);
        }

        sprintf(buff2,buff);
        i++;

    }

    close(fdpipe);
    close (fd);


}
