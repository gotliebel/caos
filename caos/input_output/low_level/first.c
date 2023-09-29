#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int input_file = open(argv[1], O_RDONLY);
    int output_numbers = open(argv[2], O_RDWR | O_CREAT, 0666);
    int output_else = open(argv[3], O_RDWR | O_CREAT, 0666);
    char buffer[10];
    long attempt_to_read = 10;
    int is_over = 1;
    while (is_over == 1) {
        long previous = attempt_to_read;
        attempt_to_read = read(input_file, buffer, 10);
        if (previous != attempt_to_read) {
            is_over = 0;
        }
        for (int i = 0; i < attempt_to_read; i++) {
            if (buffer[i] >= '0' && buffer[i] <= '9') {
                write(output_numbers, &buffer[i], 1);
            } else {
                write(output_else, &buffer[i], 1);
            }
        }
    }
    close(input_file);
    close(output_numbers);
    close(output_else);
    return 0;
}