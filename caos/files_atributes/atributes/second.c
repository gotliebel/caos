#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
    struct stat file_info;
    char file_name[1000] = {0};
    while (1) {
        if (!fgets(file_name, 1000, stdin)) {
            break;
        }
        for (int i = 0; i < 1000; i++) {
            if (file_name[i] == EOF || file_name[i] == '\n') {
                file_name[i] = '\0';
                break;
            }
        }
        if (lstat(file_name, &file_info) == -1) {
            break;
        }
        stat(file_name, &file_info);
        if ((S_IEXEC & file_info.st_mode) != 0) {
            int input = open(file_name, O_RDONLY | O_CREAT, 0666);
            char buffer[4] = {0};
            read(input, buffer, 4);
            if (buffer[0] == '#' && buffer[1] == '!') {
                char interpretator[1000] = {0};
                lseek(input, 2, SEEK_SET);
                read(input, interpretator, 1000);
                char real_interpretator[1000] = {0};
                for (int i = 0; i < 1000; i++) {
                    if (interpretator[i] == EOF || interpretator[i] == '\n') {
                        real_interpretator[i] = '\0';
                        break;
                    }
                    real_interpretator[i] = interpretator[i];
                }
                if (lstat(real_interpretator, &file_info) == -1) {
                    printf("%s\n", file_name);
                }
                continue;
            }
            if (buffer[0] == '\x7f' && buffer[1] == 'E' && buffer[2] == 'L' &&
                buffer[3] == 'F') {
                continue;
            }
            printf("%s\n", file_name);
        }
    }
    return 0;
}