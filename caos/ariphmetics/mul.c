#include <stdint.h>

void sum(ITYPE first, ITYPE second, ITYPE* res, int* CF)
{
    *res = 0;
    ITYPE one = 1;
    ITYPE first_i_bit = 0;
    ITYPE second_i_bit = 0;
    ITYPE over = 0;
    for (int i = 0; i < 8 * sizeof(ITYPE); i++) {
        first_i_bit = (((one << i) & first) >> i);
        second_i_bit = (((one << i) & second) >> i);
        *res =
            (*res | (((1 - first_i_bit) & (1 - second_i_bit) & over) |
                     ((1 - first_i_bit) & second_i_bit & (1 - over)) |
                     (first_i_bit & (1 - second_i_bit) & (1 - over)) |
                     (first_i_bit & second_i_bit & over))
                        << i);
        over = ((1 - first_i_bit) & second_i_bit & over) |
               (first_i_bit & (1 - second_i_bit) & over) |
               (first_i_bit & second_i_bit & (1 - over)) |
               (first_i_bit & second_i_bit & over);
    }
    if (over == 1) {
        *CF = 1;
    } else {
        *CF = 0;
    }
}

void mul(ITYPE first, ITYPE second, ITYPE* res, int* CF)
{
    ITYPE second_i_bit = 0;
    ITYPE one = 1;
    *res = 0;
    ITYPE res_sum_int = 0;
    ITYPE* res_sum = &res_sum_int;
    for (int i = 0; i < 8 * sizeof(ITYPE); i++) {
        second_i_bit = (((one << i) & second) >> i);
        if (second_i_bit == 1) {
            sum((first << i), *res, res_sum, CF);
            *res = *res_sum;
        }
    }
}
