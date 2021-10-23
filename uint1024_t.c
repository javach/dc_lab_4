#include "uint1024_t.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

const uint64_t RADIX = 4294967296; // 2^32
const char ALPHABET[] = "0123456789ABCDEF";

void throw_exception() {
    printf("Undefined behaviour exception\n", stderr);
    exit(1);
}

uint1024_t new_uint1024_t() {
    uint1024_t result;
    for (int i = 0; i < 32; i++) {
        result.digits[i] = 0;
    }
    return result;
}

uint1024_t from_uint(unsigned int x) {
    uint1024_t result = new_uint1024_t();
    result.digits[31] = x;
    return result;
}

uint1024_t add_op(uint1024_t x, uint1024_t y) {
    uint1024_t result = new_uint1024_t();

    int carry = 0;
    for (int i = 31; i >= 0; i--) {
        uint64_t sum = x.digits[i];
        sum += y.digits[i];
        sum += carry;
        result.digits[i] = sum % RADIX;

        carry = sum >= RADIX ? 1 : 0;

        if (carry == 1 && i == 0)
            throw_exception();
    }

    return result;
}

uint1024_t subtr_op(uint1024_t x, uint1024_t y) {
    uint1024_t result = new_uint1024_t();

    for (int i = 31; i >= 0; i--) {
        if (x.digits[i] >= y.digits[i]) {
            result.digits[i] = x.digits[i] - y.digits[i];
            continue;
        }
        if (i == 0)
            throw_exception();

        for (int j = i - 1; j >= 0; j--) {
            if (x.digits[j] > 0) {
                x.digits[j]--;
                uint64_t digit = RADIX;
                digit -= y.digits[i];
                digit += x.digits[i];

                result.digits[i] = (uint32_t) digit;
                break;
            } else {
                if (j == 0)
                    throw_exception();
                x.digits[j] = RADIX - 1;
            }
        }
    }

    return result;
}

uint1024_t shift(uint1024_t x, int pos) {
    uint1024_t result = new_uint1024_t();
    for (int i = 32 - pos; i >= 0; i--) {
        result.digits[i] = x.digits[i + pos];
    }
    return result;
}

uint1024_t mult_op_one_digit(uint1024_t x, uint32_t y) {
    uint1024_t result = new_uint1024_t();
    for (int i = 31; i >= 0; i--) {
        uint64_t product = x.digits[i];
        product *= y;
        product += result.digits[i];

        result.digits[i] = product % RADIX;
        uint1024_t carrier = new_uint1024_t();
        carrier.digits[i - 1] = product / RADIX;
        result = add_op(result, carrier);
    }
    return result;
}

uint1024_t mult_op(uint1024_t x, uint1024_t y) {
    uint1024_t result = new_uint1024_t();

    for (int i = 31; i >= 0; i--) {
        uint1024_t temp = mult_op_one_digit(x, y.digits[i]);
        temp = shift(temp, 31 - i);
        result = add_op(result, temp);
    }

    return result;
}

// String repr functions

char *convert_to_hex(uint32_t x) {
    char *result = (char *)malloc(8 * sizeof(char));
    for (int i = 7; i >= 0; i--) {
        if (x > 0) {
            result[i] = ALPHABET[x % 16];
            x /= 16;
        } else {
            result[i] = '0';
        }
    }
    return result;
}

void printf_without_leading_zeroes(char *x) {
    int started = 0;
    for (int i = 0; i < strlen(x); i++) {
        if (x[i] == '0' && !started)
            continue;
        if (x[i] != '0')
            started = 1;

        printf("%c", x[i]);
    }
}

void printf_value(uint1024_t x) {
    int started = 0;
    for (int i = 0; i < 32; i++) {
        if (x.digits[i] == 0 && !started)
            continue;
        if (x.digits[i] != 0 && !started) {
            printf_without_leading_zeroes(convert_to_hex(x.digits[i]));
            started = 1;
        } else {
            printf("%s", convert_to_hex(x.digits[i]));
        }
    }
    if (!started)
        printf("0");
    printf("\n");
}

void scanf_value(uint1024_t *x) {
    char *str = (char *)malloc(sizeof(char) * 310);
    scanf("%s", str);
    *x = new_uint1024_t();

    for (int i = strlen(str) - 1; i >= 0; i--) {
        int power = strlen(str) - i - 1;
        char digit = str[i] - '0';
        uint1024_t temp = from_uint(digit);
        for (int i = 0; i < power; i++) {
            temp = mult_op(temp, from_uint(10));
        }

        *x = add_op(*x, temp);
    }
}