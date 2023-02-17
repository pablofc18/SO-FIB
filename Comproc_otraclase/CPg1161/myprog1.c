#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

void error_exit(char * msg, int exstatus) {
    perror(msg);
    exit(exstatus);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: ./myprog1 <mas de 1 arg> ...\n");
        exit(EXIT_FAILURE);
    }

    // creamos pipe sin nombre
    int fdpipe[2];
    if (pipe(fdpipe) < 0) error_exit("error pipe\n", 1);

    // proceso n+1 para mutar a ./micat
    int pid = fork();
    if (pid == -1) error_exit("error fork\n",1);
    else if (pid == 0) {
        // creamos pipe con nombre
        if (mknod("MIPIPE", S_IFIFO|0600, 0) < 0 && errno != EEXIST) error_exit("error mknod\n",1);

        // muta a ./micat
        close(fdpipe[1]);
        dup2(fdpipe[0],10);
        close(fdpipe[0]);

        // abrimos pipe con nombre (sabemos q ya esta creada)
        int fdnamedpipe = open("MIPIPE", O_WRONLY);
        if (fdnamedpipe == -1) error_exit("error open pipe\n",1);

        // escribir a pipe con nombre
        dup2(fdnamedpipe,20);
        close(fdnamedpipe);

        execlp("./micat", "./micat", (char*)NULL);
        error_exit("error execlp micat\n",1);
    }

    // num parametros
    int n = argc;
    for (int i = 1; i < n; ++i) {
        int pid = fork();
        if (pid == -1) error_exit("error fork\n", 1);
        else if (pid == 0) {
            // muta a cat + argv[i];
            close(fdpipe[0]);
            dup2(fdpipe[1],1);
            close(fdpipe[1]);

            execlp("cat", "cat", argv[i], (char*)NULL);
            error_exit("error execlp\n",1);
        }
    }

    // parent cierra todos los canales abiertos
    close (fdpipe[0]);
    close (fdpipe[1]);

    while (waitpid(-1,NULL,0) > 0);
    printf("Padre finish cuh\n");
}
