#include <sys/syscall.h>
long syscall(long number, ...);
void my_write(int fd, const void* buf, unsigned long count)
{
    syscall(SYS_write, fd, buf, count);
}
void my_exit_group(int status)
{
    syscall(SYS_exit_group, status, 0, 0);
}
void _start()
{
    const char hello[] = "Hello, World!\n";
    my_write(1, hello, sizeof(hello) - 1);
    my_exit_group(0);
}/*
#include <stdio.h>
 /*for (int i = 0; i < 10000; ++i) {
        buffer[i] = '`';
    }*/
/*int size = 0;
    while (buffer[size] != '`') {
        size++;
    }*/
/*char new_buffer[size];
for (int i = 0; i < size; ++i) {
    new_buffer[i] = buffer[i];
}*/
/*
int main() {
  char buf[10] = {'m'};
  for (int i = 0; i < 10; ++i) {
    printf("%c  ", buf[i]);
  }
}*/