#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    char* end;
    int number = (int)strtol(argv[1], &end, 10);
    pid_t pid;
    int cur = 1;
    while (number > 0) {
        pid = fork();
        if (pid > 0) {
            int wstatus = 0;
            waitpid(pid, &wstatus, 0);
            exit(0);
        } else {
            printf("%d ", cur);
            fflush(stdout);
        }
        number -= 1;
        cur += 1;
    }
    return 0;
}