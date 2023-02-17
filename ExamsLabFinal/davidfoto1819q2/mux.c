#include <stdlib.h>
#include <unistd.h>

/*
**
**vaya cigarro nene
**
*/

int main(int argc, char** argv) {

    int r;
    char ch;
    int r2;
    while ((r = read(20,&ch,sizeof(ch))) > 0 && (r2 = read(21,&ch,sizeof(ch))) > 0) {
        write(1,&ch,r);
    }

}
