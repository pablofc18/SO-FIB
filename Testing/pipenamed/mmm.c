#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char** argv) {
    char buff[64];
    int r;
    while ((r = read(0,&buff,strlen(buff))) > 0) {
        write(69,&buff,r);
    }
}
