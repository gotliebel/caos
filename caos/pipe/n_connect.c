#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int n = argc - 1;
    int pipefd[2];
    pipe(pipefd);
    pid_t pid_first = fork();
    if (pid_first > 0) {
        int wstatus = 0;
        waitpid(pid_first, &wstatus, 0);
        close(pipefd[1]);
    } else {
        dup2(pipefd[1], 1);
        execlp(argv[1], argv[1], NULL);
    }
    int pipefd2[2];
    pipe(pipefd2);
    for (int i = 0; i < n - 2; i++) {
        pid_t pid = fork();
        if (pid > 0) {
            int ws = 0;
            waitpid(pid, &ws, 0);
            close(pipefd2[1]);
            pipefd[0] = pipefd2[0];
            pipe(pipefd2);
        } else {
            dup2(pipefd[0], 0);
            dup2(pipefd2[1], 1);
            execlp(argv[i + 2], argv[i + 2], NULL);
        }
    }
    pid_t pid_second = fork();
    if (pid_second > 0) {
        int wstatus = 0;
        waitpid(pid_second, &wstatus, 0);
        close(pipefd[0]);
        close(pipefd2[0]);
        close(pipefd2[1]);
    } else {
        dup2(pipefd[0], 0);
        execlp(argv[n], argv[n], NULL);
    }
    return 0;
}