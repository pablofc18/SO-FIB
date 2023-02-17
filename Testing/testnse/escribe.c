#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	char buff[64];

	int fd = open("mipipa", O_RDONLY);
	if (fd == -1) {
		printf("EERROROROR\n");
		exit(EXIT_FAILURE);
	}

	int r;
	while((r=read(fd,&buff,64)) > 0) {
		write(1,&buff,r);
	}

	close (fd);
}
