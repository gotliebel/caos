#include <stdint.h>

typedef enum {
    PlusZero = 0x00,
    MinusZero = 0x01,
    PlusInf = 0xF0,
    MinusInf = 0xF1,
    PlusRegular = 0x10,
    MinusRegular = 0x11,
    PlusDenormal = 0x20,
    MinusDenormal = 0x21,
    SignalingNaN = 0x30,
    QuietNaN = 0x31
} float_class_t;

extern float_class_t classify(double* value_ptr)
{
    void* value_ptr_as_void = value_ptr;
    uint64_t* value_ptr_as_uint = value_ptr_as_void;
    uint64_t value = *value_ptr_as_uint;
    uint64_t one = 1;
    uint64_t sign = (((one << 63) & value) >> 63);
    uint64_t mantissa = 0;
    uint64_t shift = 0;
    for (int i = 0; i < 52; ++i) {
        uint64_t i_bit = (((one << i) & value) >> i);
        mantissa = (mantissa | (i_bit << i));
    }
    value = value >> 52;
    for (int i = 0; i < 11; ++i) {
        uint64_t i_bit = (((one << i) & value) >> i);
        shift = (shift | (i_bit << i));
    }
    if (sign == 0 && shift == 0 && mantissa == 0) {
        return PlusZero;
    } else if (sign == 1 && shift == 0 && mantissa == 0) {
        return MinusZero;
    } else if (sign == 0 && shift == 2047 && mantissa == 0) {
        return PlusInf;
    } else if (sign == 1 && shift == 2047 && mantissa == 0) {
        return MinusInf;
    } else if (sign == 0 && shift == 0 && mantissa != 0) {
        return PlusDenormal;
    } else if (sign == 1 && shift == 0 && mantissa != 0) {
        return MinusDenormal;
    } else if (shift == 2047 && mantissa != 0) {
        uint64_t bit = (((one << 51) & mantissa) >> 51);
        if (bit == 1) {
            return QuietNaN;
        } else {
            return SignalingNaN;
        }
    } else if (sign == 0) {
        return PlusRegular;
    } else {
        return MinusRegular;
    }
}
