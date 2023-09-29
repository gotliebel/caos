#include <sys/syscall.h>

long syscall(long number, ...);

void _start()
{
  char text[5];
  for (long last_readen = 5; last_readen == 5;) {
    last_readen = syscall(SYS_read, 0, text, 5);
    syscall(SYS_write, 1, text, last_readen);
  }
  syscall(SYS_exit_group, 0);
  return;
}