#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    char* file_name = argv[1];
    char* pattern = argv[2];
    int input = open(file_name, O_RDONLY);
    struct stat file_info;
    fstat(input, &file_info);
    long size_file = file_info.st_size;
    char* ptr = mmap(NULL, size_file, PROT_READ, MAP_PRIVATE, input, 0);
    if (MAP_FAILED == ptr) {
        close(input);
        _exit(1);
    }
    int indexes[1000] = {0};
    int index = 0;
    long size_pattern = 0;
    for (int i = 0; i < 1000; i++) {
        if (pattern[i] == '\0') {
            size_pattern = i;
            break;
        }
    }
    bool is_start_index = true;
    for (int i = 0; i < size_file - size_pattern + 1; i++) {
        is_start_index = true;
        for (int j = 0; j < size_pattern; j++) {
            if (pattern[j] != ptr[i + j]) {
                is_start_index = false;
                break;
            }
        }
        if (is_start_index) {
            indexes[index] = i;
            index += 1;
        }
    }
    for (int i = 0; i < index; i++) {
        printf("%d ", indexes[i]);
    }
    munmap(ptr, size_file);
    close(input);
    return 0;
}