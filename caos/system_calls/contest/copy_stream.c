#include <sys/syscall.h>
long syscall(long number, ...);

void my_exit_group(int status)
{
    syscall(SYS_exit_group, status);
}
void _start()
{
    char buffer[10];
    long attempt_to_read = 10;
    int is_over = 1;
    while (is_over == 1) {
        long previous = attempt_to_read;
        attempt_to_read = syscall(SYS_read, 0, buffer, 10);
        syscall(SYS_write, 1, buffer, attempt_to_read);
        if (previous != attempt_to_read) {
            is_over = 0;
        }
    }
    my_exit_group(0);
}