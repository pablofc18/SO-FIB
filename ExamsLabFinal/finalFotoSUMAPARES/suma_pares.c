#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        perror("Usage: suma_pares <1arg> <2arg>\n");
        exit(EXIT_FAILURE);
    }

    int pipefd[2];
    if (pipe(pipefd) < 0) {
        perror("EROR PIP\n");
        exit(1);
    }

    // muta a solo_pares
    int pid = fork();
    if (pid == -1) {
        perror("Error fork\n");
        exit(1);
    }
    else if (pid == 0) {
        dup2(pipefd[0],0);
        close(pipefd[1]);
        execlp("./solo_pares", "./solo_pares", (char*)NULL);
        perror("Erro execlp\n");
        exit(1);
    }

    // muta a suma
    pid = fork();
    if (pid == -1) {
        perror("EROR PIP\n");
        exit(1);
    }
    else if (pid == 0) {
        dup2(pipefd[1],1);
        close(pipefd[1]);
        // argv[2] resultado de suma
        execlp("./suma", "./suma", argv[2], (char*)NULL);
        perror("eReore\n");
        exit(1);
    }

	close(pipefd[0]);
	close(pipefd[1]);

    while (waitpid(-1,NULL,0) > 0);




}
