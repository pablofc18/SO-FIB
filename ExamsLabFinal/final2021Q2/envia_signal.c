#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

int main(int argc, char*argv[]) {
    char buff[64];

    if (mknod("mypipe", S_IFIFO|0600,0) < 0 && errno != EEXIST) {
        perror("ERROR pipe\n");
        exit(EXIT_FAILURE);
    }

    // read from pipe mypipe
    int fifo = open("mypipe", O_RDONLY);
    if (errno == ENXIO) {
        printf("ERrOR");
        exit(1);
    }


    //printf("****%d****\n", fd);
    printf("****%d****\n", fifo);


    int r;
    int i = 0;
    int nums[2];
    int number;
    while ((r = read(fifo, &number, sizeof(int))) > 0) {
        sprintf(buff,"%d",number);
        write(1,&buff,strlen(buff));
        printf("\n");
        nums[i] = atoi(buff);
        ++i;
        if (i == 2) {
            //sprintf(buff, "El proceso %d term: %d\n", nums[0], nums[1]);

            printf("%d", nums[0]+nums[1]);
            // transformamos el numero recibido a la signal correspondiente (kill -l)
            if (nums[1] == 1) {
                // sigint = 2
                nums[1] == 2;
                kill(nums[0],SIGINT);
            }
            else if (nums[1] == 2) {
                // sigusr1 = 10
                nums[1] == 10;
                kill(nums[0],SIGUSR1);
            }
            else if (nums[1] == 3) {
                // sigusr2 = 12
                nums[1] == 12;
                kill(nums[0],SIGUSR2);
            }

            // enviamos signal
            //kill(nums[0],nums[1]);
            //write(1,buff,strlen(buff));
            i = 0;
        }
    }
    close (fifo);

}
