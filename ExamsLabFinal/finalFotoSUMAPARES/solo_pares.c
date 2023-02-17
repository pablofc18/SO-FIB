#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main (int argc, char* argv[]) {

    int * vec_int = malloc(128*sizeof(int));

    char buff[64];
    int i = 0;
    int r;
    int num;
    while ((r = read(0,&buff,sizeof(int))) > 0) {
        num = atoi(buff);
        if (i%2 == 0) {
            /* char buff2[64]; */
            /* sprintf(buff2,"%d",num); */
            /* write(1,buff2,sizeof(num)); */
            vec_int[i/2] = num;
        }
        ++i;
    }

    for (int i = 0; i < 10; ++i) {
        printf("%d\n",vec_int[i]);
    }

    free(vec_int);
}
