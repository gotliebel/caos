#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    char* cmd = argv[1];
    char* in = argv[2];
    int pipefd[2]; // pipefd[0] - read, pipefd[1] - write
    pipe(pipefd);
    pid_t pid = fork();

    if (pid > 0) {
        int wstatus = 0;
        waitpid(pid, &wstatus, 0);
        close(pipefd[1]);
        char buffer[10];
        long attempt_to_read = 10;
        bool is_over = true;
        long sum_bytes = 0;
        while (is_over) {
            long previous = attempt_to_read;
            attempt_to_read = read(pipefd[0], buffer, 10);
            sum_bytes += attempt_to_read;
            if (previous != attempt_to_read) {
                is_over = false;
            }
        }
        close(pipefd[0]);
        printf("%ld", sum_bytes);
    } else {
        close(pipefd[0]);
        dup2(pipefd[1], 1);
        execlp(cmd, cmd, in, NULL);
        close(pipefd[1]);
        exit(0);
    }
    return 0;
}