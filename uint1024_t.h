#include <stdint.h>
struct uint1024_t {
    uint32_t digits[32];
};

typedef struct uint1024_t uint1024_t;

uint1024_t new_uint1024_t();

uint1024_t from_uint(unsigned int x);

uint1024_t add_op(uint1024_t x, uint1024_t y);

uint1024_t subtr_op(uint1024_t x, uint1024_t y);

uint1024_t mult_op(uint1024_t x, uint1024_t y);

void printf_value(uint1024_t x);

void scanf_value(uint1024_t *x);