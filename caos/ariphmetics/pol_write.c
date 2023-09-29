#include <stdint.h>
#include <stdio.h>

int main()
{
    uint64_t res = 0;
    uint64_t cur = 0;
    uint64_t one = 1;
    int symb;
    while ((symb = getchar()) != EOF) {
        if (symb == '&') {
            res = res & cur;
            cur = 0;
        } else if (symb == '|') {
            res = res | cur;
            cur = 0;
        } else if (symb == '^') {
            res = res ^ cur;
            cur = 0;
        } else if (symb == '~') {
            res = ~res;
            cur = 0;
        } else {
            if (symb >= 48 && symb <= 57) {
                symb -= 48;
                cur = cur | (one << symb);
            } else if (symb >= 65 && symb <= 90) {
                symb -= 55;
                cur = cur | (one << symb);
            } else if (symb >= 97 && symb <= 122) {
                symb -= 61;
                cur = cur | (one << symb);
            }
        }
    }
    uint64_t i_bit = 0;
    for (int i = 0; i < 10; i++) {
        i_bit = (((one << i) & res) >> i);
        if (i_bit == 1) {
            printf("%d", i);
        }
    }
    for (int i = 10; i < 36; i++) {
        i_bit = (((one << i) & res) >> i);
        if (i_bit == 1) {
            printf("%c", i + 55);
        }
    }
    for (int i = 36; i < 62; i++) {
        i_bit = (((one << i) & res) >> i);
        if (i_bit == 1) {
            printf("%c", i + 61);
        }
    }
    return 0;
}
