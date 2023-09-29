#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork();
    if (pid > 0) {
        int wstatus = 0;
        waitpid(pid, &wstatus, 0);
    }
    if (pid == 0) {
        char expression[1000];
        fgets(expression, 1000, stdin);
        int file = open("py", O_RDWR | O_CREAT, 0777);
        unsigned long len = strlen(expression);
        char buffer[] = "print(";
        write(file, buffer, 6);
        write(file, expression, len);
        write(file, ")", 1);
        execlp("python3", "python3", "py", NULL);
        perror("exec");
        exit(1);
    }
    if (pid == -1) {
        return -1;
    }
    remove("py");
    return 0;
}