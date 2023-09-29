#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    pid_t pid;
    int counter = 0;
    bool is_eof = false;
    char string[4096] = {0};
    while (true) {
        if (scanf("%s", string) == EOF) {
            break;
        } else {
            pid = fork();
            if (pid > 0) {
                int wstatus = 0;
                waitpid(pid, &wstatus, 0);
                counter += WEXITSTATUS(wstatus);
            } else if (pid == 0) {
                exit(1);
            } else {
                return -1;
            }
        }
    }
    printf("%d", counter);
    return 0;
}