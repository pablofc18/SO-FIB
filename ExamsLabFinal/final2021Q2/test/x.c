#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	int fd = open(argv[1], O_RDONLY);
	int r;
	int num;
	char buff[16];
	while ((r = read(fd,&num,sizeof(int))) > 0) {
		sprintf(buff,"%d",num);
//		int numero = num;
//		sprintf(buff, "%d", numero);
		write(1,&buff,strlen(buff));
		printf("\n");
		//lseek(fd,4,SEEK_CUR);
	}
	close (fd);
}
