#include "socketMng.c"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define MAX 128

void error_exit(char * msg, int status) {
    perror(msg);
    exit(status);
}

int main(int argc, char * argv[]) {
    if (argc != 2) {
        error_exit("Usage: prClientSocket socketPath\n", 1);
    }

    char buff[MAX];

    int connectionFD = clientConnection(argv[1]);
    if (connectionFD < 0) error_exit("Error connecting to socket\n", 1);

    int ret = read(connectionFD, &buff, strlen(buff));
    if (ret < 0) error_exit("Error reading from connection\n", 1);

    ret = write(1, &buff, ret);
    if (ret < 0) error_exit("Error writng sto\n", 1);

    sprintf(buff, "Hello Sir\n");
    ret = write(connectionFD, &buff, strlen(buff));
    if (ret < 0) error_exit("Error writing on connection\n", 1);

    /* int r; */
    /* while (r = read(0,&buff,MAX) > 0) write(connectionFD, &buff, r); */
    // MISMO PROBLEMA QUE EN LECTOR ESCRITOR SOLO LEE UN BYTE ¿?¿?¿?¿?¿?
    while (write(connectionFD, &buff, read(0,&buff,MAX)));

    closeConnection(connectionFD);
}
