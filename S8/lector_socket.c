#include "socketMng.c"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX 128

void error_exit(char * msg, int status) {
    perror(msg);
    exit(status);
}

int main(int argc, char * argv[]) {
    if (argc != 2) {
        error_exit("Usage: prClientSocket socketPath\n",1);
    }

    char buff[MAX];

    int socketFD = createSocket(argv[1]);
    if (socketFD < 0) error_exit("Error creating socket\n", 1);

    int connectionFD = serverConnection(socketFD);
    if (connectionFD < 0) error_exit("Error stablishing connection\n", 1);

    int ret = write(connectionFD, &buff, strlen(buff));
    if (ret < 0) error_exit("Error writing on connection\n", 1);

    // escribirá por pantalla lo que lea del socket
    /* int r; */
    /* while (r = read(connectionFD, &buff, MAX) > 0) write(1,&buff, r); */
    // MISMO PROBLEMA QUE EN LECTOR ESCRITOR SOLO LEE UN BYTE ¿?¿?¿?¿?¿?
    while (write(1,&buff, read(connectionFD, &buff, MAX)));

    closeConnection(connectionFD);
    deleteSocket(socketFD, argv[1]);
}
