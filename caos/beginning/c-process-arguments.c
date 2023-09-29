#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    long sum = 0;
    long current_sum = 0;
    for (int i = 1; i < argc; ++i) {
        current_sum = sum;
        sum += atol(argv[i]);
        if (current_sum == sum) {
            printf("%s\n", argv[i]);
        } else {
            for (int j = 0; j < strlen(argv[i]); ++j) {
                if ((argv[i][j] - '0' < 0) || (argv[i][j] - '0' > 9)) {
                    sum -= atol(argv[i]);
                    printf("%s\n", argv[i]);
                    break;
                }
            }
        }
    }
    printf("%li\n", sum);
    return 0;
}
