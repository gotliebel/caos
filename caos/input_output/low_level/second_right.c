#include <inttypes.h>

#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct Item {
    int value;
    uint32_t next_pointer;
} item_t;
int main(int agrc, char* argv[])
{
    char* input_file_name = argv[1];
    int input_file = open(input_file_name, O_RDONLY | O_CREAT, 0644);
    item_t item;
    if (read(input_file, &item, 8) == 0) {
        close(input_file);
        return 0;
    }
    printf("%d ", item.value);
    lseek(input_file, item.next_pointer, SEEK_SET);
    if (item.next_pointer == 0) {
        return 0;
    }
    long attempt_to_read;
    while (1) {
        attempt_to_read = read(input_file, &item, 8);
        if (attempt_to_read != 8) {
            break;
        }
        printf("%d ", item.value);
        lseek(input_file, item.next_pointer, SEEK_SET);
        if (item.next_pointer == 0) {
            break;
        }
    }
    close(input_file);
}