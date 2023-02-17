#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char** argv) {
    if (argc != 2) {
        perror("Usage: ./spawnA <1arg>\n");
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[1]);

    for (int i = 0; i < n; ++i) {
        int pid = fork();
        if (pid == -1) exit(EXIT_FAILURE);
        else if (pid == 0) {
            execlp("./hijo1", "./hijo1", i, (char*)NULL);
            exit(EXIT_FAILURE);
        }
    }

    int stat;
    while (waitpid(-1,&stat,0) > 0) {
        int pid = fork();
        if (pid == -1) exit(EXIT_FAILURE);
        else if (pid == 0) {
            execlp("./hijo1", "./hijo1", WEXITSTATUS(stat), (char*)NULL);
            exit(EXIT_FAILURE);
        }
    }
}
