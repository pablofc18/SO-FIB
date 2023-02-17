#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	char buff[64];

	if (mknod("mipipa", S_IFIFO|0600, 0) < 0 && errno != EEXIST) {
		exit(EXIT_FAILURE);
	}

	int fd = open("mipipa", O_WRONLY);
	if (fd == -1) {
		printf("EERROROROR\n");
		exit(EXIT_FAILURE);
	}

	int r;
	while((r=read(0,&buff,64)) > 0) {
		write(fd,&buff,r);
	}

	close (fd);
}
