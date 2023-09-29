#include <fcntl.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

const int kStructSize = 8;

typedef struct Item {
  int value;
  uint32_t next_pointer;
} item_t;

void Print(int file_name, item_t list)
{
  while (true) {
    if (read(file_name, &list, kStructSize) != kStructSize) {
      return;
    }
    printf("%d ", list.value);
    lseek(file_name, list.next_pointer, SEEK_SET);
    if (!list.next_pointer) {
      return;
    }
  }
}

bool Check(int file_name, item_t list)
{
  if (read(file_name, &list, kStructSize)) {
    return true;
  }
  return false;
}

int main(int argc, char* argv[])
{
  int file = open(argv[1], O_RDONLY | O_CREAT, 0666);
  item_t list;
  if (!Check(file, list)) {
    close(file);
  } else {
    printf("%d ", list.value);
    lseek(file, list.next_pointer, SEEK_SET);
    if (list.next_pointer) {
      Print(file, list);
      close(file);
    }
  }
}