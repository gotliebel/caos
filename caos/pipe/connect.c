#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
  char* cmd1 = argv[1];
  char* cmd2 = argv[2];
  int pipefd[2];
  pipe(pipefd);
  pid_t pid_first = fork();
  if (pid_first > 0) {
    int wstatus = 0;
    waitpid(pid_first, &wstatus, 0);
  } else {
    dup2(pipefd[1], 1);
    execlp(cmd1, cmd1, NULL);
  }
  close(pipefd[1]);
  pid_t pid_second = fork();
  if (pid_second > 0) {
    int wstatus = 0;
    waitpid(pid_second, &wstatus, 0);
  } else {
    dup2(pipefd[0], 0);
    execlp(cmd2, cmd2, NULL);
  }
  return 0;
}