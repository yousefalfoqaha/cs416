#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  pid_t cpid, result;
  int status;

  cpid = fork();

  if (cpid == 0) {
    printf("Child process running...\n");
    sleep(5);
    exit(15);
  }

  do {
    result = waitpid(cpid, &status, WNOHANG);

    if (result == 0) {
      printf("Waiting for child process to finish\n");
      sleep(1);
    }
  } while (result == 0);

  if (WIFEXITED(status)) {
    printf("Finished task.\n");
  }

  if (result > 0) {
    printf("Child process ran successfully.\n");
  } else {
    printf("An error occurred.\n");
  }

  printf("Exit status: %d\n", WEXITSTATUS(status));

  return 0;
}
