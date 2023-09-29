#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    char first_string[1000] = {0};
    fgets(first_string, 1000, stdin);
    char second_string[1000] = {0};
    fgets(second_string, 1000, stdin);
    char last_string[2] = {0};
    fgets(last_string, 2, stdin);
    char http_host[1000] = {0};
    char query_string[1000] = {0};
    char request_method[1000] = {0};
    char script_name[1000] = {0};
    char http[1000] = {0};
    long index = 0;
    long index_insert = 0;
    long len_first = strlen(first_string);
    while (first_string[index] != ' ') {
        request_method[index_insert] = first_string[index];
        index += 1;
        index_insert += 1;
    }
    setenv("REQUEST_METHOD", request_method, 1);
    index += 1;
    index_insert = 1;
    while (index < len_first && first_string[index] != '?' &&
           first_string[index] != ' ') {
        script_name[index_insert] = first_string[index];
        index += 1;
        index_insert += 1;
    }
    script_name[0] = '.';
    setenv("SCRIPT_NAME", script_name, 1);
    index_insert = 0;
    if (first_string[index] == '?') {
        index += 1;
        while (index < len_first && first_string[index] != ' ') {
            query_string[index_insert] = first_string[index];
            index += 1;
            index_insert += 1;
        }
    }
    setenv("QUERY_STRING", query_string, 1);
    index += 1;
    index_insert = 0;
    while (index < len_first && index != len_first - 1) {
        http[index_insert] = first_string[index];
        index += 1;
        index_insert += 1;
    }
    long len_second = strlen(second_string);
    index_insert = 0;
    for (long i = 6; i < len_second; i++) {
        http_host[index_insert] = second_string[i];
        index_insert += 1;
    }
    struct stat file_info;
    stat(script_name, &file_info);
    if (lstat(script_name, &file_info) == -1) {
        printf("%s 404 ERROR\n\n", http);
        return 0;
    }
    if ((S_IEXEC & file_info.st_mode) == 0) {
        printf("%s 403 ERROR\n\n", http);
        return 0;
    }
    printf("TEST SOMETHING\n");
    pid_t pid = fork();
    if (pid > 0) {
        int wstatus = 0;
        waitpid(pid, &wstatus, 0);
    } else {
        execlp(script_name, script_name, NULL);
        exit(0);
    }
    return 0;
}