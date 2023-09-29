#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void MergeSort(int, int);
void Merge(int, int, int, int);

int main(int agrc, char* argv[])
{
    char* input_file_name = argv[1];
    int input_file = open(input_file_name, O_RDWR | O_CREAT, 0666);
    struct stat file_info;
    fstat(input_file, &file_info);
    long size = file_info.st_size;
    if (size == 0) {
        return 0;
    }
    size /= 4;
    MergeSort(input_file, size);
    close(input_file);
}

void MergeSort(int input_file, int size)
{
    for (int i = 1; i < size; i *= 2) {
        for (int j = 0; j < size - i; j += 2 * i) {
            if (j + 2 * i < size) {
                Merge(input_file, j, j + i, j + 2 * i);
            } else {
                Merge(input_file, j, j + i, size);
            }
        }
    }
}
void Merge(int input_file, int left, int mid, int right)
{
    int it1 = 0;
    int it2 = 0;
    int value_left_it1 = 0;
    int value_mid_it2 = 0;
    int output_file = open("something.txt", O_RDWR | O_CREAT, 0666);
    while (left + it1 < mid && mid + it2 < right) {
        lseek(input_file, (left + it1) * 4, SEEK_SET);
        read(input_file, &value_left_it1, 4);
        lseek(input_file, (mid + it2) * 4, SEEK_SET);

        read(input_file, &value_mid_it2, 4);
        if (value_left_it1 < value_mid_it2) {
            lseek(output_file, (it1 + it2) * 4, SEEK_SET);
            write(output_file, &value_left_it1, 4);
            it1 += 1;
        } else {
            lseek(output_file, (it1 + it2) * 4, SEEK_SET);
            write(output_file, &value_mid_it2, 4);
            it2 += 1;
        }
    }
    while (left + it1 < mid) {
        lseek(input_file, (left + it1) * 4, SEEK_SET);
        read(input_file, &value_left_it1, 4);
        lseek(output_file, (it1 + it2) * 4, SEEK_SET);
        write(output_file, &value_left_it1, 4);
        it1 += 1;
    }
    while (mid + it2 < right) {
        lseek(input_file, (mid + it2) * 4, SEEK_SET);
        read(input_file, &value_mid_it2, 4);
        lseek(output_file, (it1 + it2) * 4, SEEK_SET);
        write(output_file, &value_mid_it2, 4);
        it2 += 1;
    }

    int value = 0;
    for (int i = 0; i < it1 + it2; i++) {
        lseek(output_file, i * 4, SEEK_SET);
        read(output_file, &value, 4);
        lseek(input_file, (left + i) * 4, SEEK_SET);
        write(input_file, &value, 4);
    }
    close(output_file);
    remove("something.txt");
}