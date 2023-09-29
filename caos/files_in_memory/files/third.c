#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    char* file_name = argv[1];
    char* end;
    int matrix_size = (int)strtol(argv[2], &end, 10);
    int cell_size = (int)strtol(argv[3], &end, 10);
    const int max_value = matrix_size * matrix_size;
    int input = open(file_name, O_RDWR | O_CREAT, 0666);
    lseek(
        input,
        matrix_size * matrix_size * cell_size + matrix_size - 2,
        SEEK_SET);
    write(input, "\0", 1);
    char* ptr = mmap(
        NULL,
        matrix_size * matrix_size * cell_size + matrix_size - 2,
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        input,
        0);
    if (MAP_FAILED == ptr) {
        close(input);
        _exit(1);
    }
    int value = 1;
    int** matrix = (int**)malloc(matrix_size * sizeof(int*));
    for (int i = 0; i < matrix_size; i++) {
        matrix[i] = (int*)malloc(matrix_size * sizeof(int));
        matrix[0][i] = value;
        value += 1;
    }
    int i = 0;
    int j = matrix_size - 1;
    int number_moves = matrix_size - 1;
    while (value <= max_value) {
        for (int k = 0; k < number_moves; k++) {
            i += 1;
            matrix[i][j] = value;
            value += 1;
        }
        for (int k = 0; k < number_moves; k++) {
            j -= 1;
            matrix[i][j] = value;
            value += 1;
        }
        number_moves -= 1;
        for (int k = 0; k < number_moves; k++) {
            i -= 1;
            matrix[i][j] = value;
            value += 1;
        }
        for (int k = 0; k < number_moves; k++) {
            j += 1;
            matrix[i][j] = value;
            value += 1;
        }
        number_moves -= 1;
    }
    for (int k = 0; k < matrix_size; k++) {
        for (int l = 0; l < matrix_size; l++) {
            char num[cell_size + 1];
            if (sprintf(num, "%d", matrix[k][l]) < 0) {
                break;
            }
            int len_number = strlen(num);
            int index = matrix_size * cell_size * k + cell_size * l + k;
            for (int m = 0; m < cell_size - len_number; m++) {
                *(ptr + index) = ' ';
                index += 1;
            }
            for (int m = 0; m < len_number; m++) {
                *(ptr + index) = num[m];
                index += 1;
            }
        }
        if (k != 0) {
            *(ptr + matrix_size * cell_size * k + k - 1) = '\n';
        }
        free(matrix[k]);
    }
    free(matrix);
    munmap(ptr, matrix_size * matrix_size * cell_size + matrix_size - 2);
    close(input);
    return 0;
}