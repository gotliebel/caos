#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
    struct stat file_info;
    char file_name[100] = {0};
    long total_size = 0;
    while (scanf("%s", file_name) != EOF) {
        stat(file_name, &file_info);
        if (lstat(file_name, &file_info) == -1) {
            break;
        }
        if (S_ISREG(file_info.st_mode) != 0) {
            total_size += file_info.st_size;
        }
    }
    printf("%lu", total_size);
    return 0;
}