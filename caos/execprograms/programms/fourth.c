#include <ctype.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int file = open("save", O_RDWR | O_CREAT, 0777);
    pid_t pid = fork();
    if (pid > 0) {
        int wstatus = 0;
        waitpid(pid, &wstatus, 0);
    } else if (pid == 0) {
        dup2(file, 1);
        dup2(file, 2);
        execlp("gcc", "gcc", argv[1], NULL);
        exit(0);
    }
    struct stat file_info;
    fstat(file, &file_info);
    long size_file = file_info.st_size;
    char* ptr = mmap(NULL, size_file, PROT_READ, MAP_PRIVATE, file, 0);
    if (MAP_FAILED == ptr) {
        close(file);
        _exit(1);
    }
    int count_errors = 0;
    int count_warnings = 0;
    int line_error = 0;
    int line_warning = 0;
    for (long i = 7; i < size_file; i++) {
        if (ptr[i] == 'r' && ptr[i - 1] == 'o' && ptr[i - 2] == 'r' &&
            ptr[i - 3] == 'r' && ptr[i - 4] == 'e' && ptr[i - 5] == ' ' &&
            ptr[i - 6] == ':') {
            int index = i - 7;
            while (isdigit(ptr[index])) {
                index--;
            }
            index--;
            char number[10] = {0};
            int j = 0;
            while (isdigit(ptr[index])) {
                number[j] = ptr[index];
                index--;
                j++;
            }
            long len = strlen(number);
            int cur_number_line = 0;
            int ten = 1;
            for (int k = len - 1; k >= 0; k--) {
                cur_number_line += ten * (number[k] - '0');
                ten *= 10;
            }
            if (cur_number_line != line_error) {
                count_errors += 1;
                line_error = cur_number_line;
            }
        }
        if (ptr[i] == 'g' && ptr[i - 1] == 'n' && ptr[i - 2] == 'i' &&
            ptr[i - 3] == 'n' && ptr[i - 4] == 'r' && ptr[i - 5] == 'a' &&
            ptr[i - 6] == 'w' && ptr[i - 7] == ' ' && ptr[i - 8] == ':') {
            int index = i - 9;
            while (isdigit(ptr[index])) {
                index--;
            }
            index--;
            char number[10] = {0};
            int j = 0;
            while (isdigit(ptr[index])) {
                number[j] = ptr[index];
                index--;
                j++;
            }
            long len = strlen(number);
            int cur_number_line = 0;
            int ten = 1;
            for (int k = len - 1; k >= 0; k--) {
                cur_number_line += ten * (number[k] - '0');
                ten *= 10;
            }
            if (cur_number_line != line_warning) {
                count_warnings += 1;
                line_warning = cur_number_line;
            }
        }
    }
    close(file);
    printf("%d %d", count_errors, count_warnings);
    munmap(ptr, size_file);
    remove("save");
    return 0;
}