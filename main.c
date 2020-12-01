#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>

static void sighandler(int signo) {
  if (signo == SIGINT) {
    printf("program exited due to SIGINT.\n");
    int file = open("sigint.txt", O_APPEND | O_WRONLY | O_CREAT, 0644);
		char m[] = "exited due to SIGINT.\n";
		write(file, m, strlen(m));
    close(file);
    exit(0);
  }

  if (signo == SIGUSR1) {
    printf("PID of parent process: %d\n", getpid());
  }
}

int main() {
  signal(SIGINT, sighandler);
  signal(SIGUSR1, sighandler);

  while (1) {
    printf("process PID: %d\n", getpid());
    sleep(1);
  }
  return 0;
}
