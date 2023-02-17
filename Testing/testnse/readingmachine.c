#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
    if (argc != 2) exit(EXIT_FAILURE);

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) exit(EXIT_FAILURE);

    int num, num2;
    /* read(fd,&num,sizeof(int)); */
    /* read(fd,&num2,sizeof(int)); */

    int r;
    char buff[8];
    while ((r = read(fd,&num,sizeof(int))) > 0) {
        sprintf(buff,"%d",num);
        num2 = atoi(buff);
        write(1,&buff,r);
        printf("\n");
		write(1,&num2,sizeof(int));
    }

    close(fd);


    char bufff[64];
//    sprintf(bufff,"-%d-,-%d-",num,num2);
	sprintf(bufff,"hol");
    write(1,bufff,strlen(bufff));
}
