#include <stdio.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    pid_t pid = 0;
    int64_t counter = 0;
    while (pid != -1) {
        counter += 1;
        pid = fork();
        if (pid > 0) {
            int wstatus = 0;
            wait(&wstatus);
            return 0;
        } else if (pid == -1) {
            printf("%lu", counter);
        }
    }
    return 0;
}