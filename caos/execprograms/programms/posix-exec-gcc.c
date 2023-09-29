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
    char expression[1000];
    fgets(expression, 1000, stdin);
    int file = open("gc.c", O_RDWR | O_CREAT, 0777);
    unsigned long len = strlen(expression);
    char buffer[] = "#include <stdio.h>\nint main() { int a = ( ";
    unsigned long buffer_len = strlen(buffer);
    write(file, buffer, buffer_len);
    write(file, expression, len);
    lseek(file, buffer_len + len - 1, SEEK_SET);
    write(file, ");\nprintf(\"%d\", a);\nreturn 0;}", 30);
    close(file);

    pid_t pid = fork();
    if (pid > 0) {
        int wstatus = 0;
        waitpid(pid, &wstatus, 0);
    } else if (pid == 0) {
        execlp("gcc", "gcc", "-o", "som", "gc.c", NULL);
        exit(0);
    }
    pid = fork();
    if (pid > 0) {
        int wstatus = 0;
        waitpid(pid, &wstatus, 0);
    } else {
        execlp("./som", "./som", NULL);
        exit(0);
    }
    remove("gc.c");
    remove("som");
    return 0;
}