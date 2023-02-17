#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

void error_y_exit (char *str)
{
  perror (str);
  exit (EXIT_FAILURE);
}

void usage ()
{
  char buffer[64];
  sprintf (buffer, "USAGE: ./userprocs username\n");
  write (1, buffer, strlen (buffer));
  exit (EXIT_FAILURE);
}

int main(int argc, char * argv[]) {
  char buff[64];

  if (argc != 2) usage ();

  int pipe1[2];

  if (pipe(pipe1) == -1) error_y_exit("Error pipe\n");

  // first child mutate to ps -l
  int pid = fork();
  if (pid == -1) error_y_exit("Error fork\n");
  else if (pid == 0) {
    close(pipe1[0]);
    // redirect std output to pipe1 read
    dup2(pipe1[1],1);
    close(pipe1[1]);

    execlp("ps", "ps", "-l", (char *) NULL);
    error_y_exit("Error execlp\n");
  }

  pid = fork();
  if (pid == -1) error_y_exit("Error fork\n");
  else if (pid == 0) {
    close (pipe1[1]);
    dup2(pipe1[0],0); // std input de la pipe socio ;)
    close (pipe1[0]);

    execlp("wc", "wc", "-l", (char *) NULL);
    error_y_exit("Error execlp\n");
  }

  close (pipe1[1]);
  close (pipe1[0]);

  while (waitpid(-1,NULL,0) > 0);
  printf("FIN\n");

}
