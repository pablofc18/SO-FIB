#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        perror("Usage: ./suma <file_name>\n");
        exit(1);
    }

    int num;
    int r;
    int sum_nums = 0;
    char buff[64];
    while ((r = read(0,&buff,sizeof(int))) > 0) {
        num = atoi(buff);
        sum_nums += num;
    }

    int fd = open(argv[1], O_CREAT|O_WRONLY|O_TRUNC, 0640);
    if (fd == -1) exit(EXIT_FAILURE);

    write(fd,&sum_nums,sizeof(int));

    close(fd);

    sprintf(buff, "La suma es %d\n", sum_nums);
    write(1,buff,strlen(buff));
}
