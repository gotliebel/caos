#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    char* file_name = argv[1];
    int input = open(file_name, O_RDONLY);
    struct stat file_info;
    fstat(input, &file_info);
    long size_file = file_info.st_size;
    int* ptr = mmap(NULL, size_file, PROT_READ, MAP_PRIVATE, input, 0);
    if (MAP_FAILED == ptr) {
        close(input);
        _exit(1);
    }
    int index = 0;
    do {
        index /= 4;
        int number = ptr[index];
        printf("%d ", number);
        index = ptr[index + 1];
    } while (index != 0);
    munmap(ptr, size_file);
    close(input);
    return 0;
}