#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int nu;
    read(0,&nu,sizeof(int));
    // Print the num to see if its correct
    printf("%d\n",nu);
}
