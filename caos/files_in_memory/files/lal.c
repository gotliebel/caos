#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
  int input = open(argv[1], O_RDWR);
  lseek(input, 4, SEEK_SET);
  char buffer[4] = {0};
  buffer[0] = 8;
  write(input, buffer, 4);
  close(input);
  return 0;
}