#include "uint1024_t.c"
#include <stdio.h>

int main() {
    uint1024_t x = from_uint(4294967295);
    uint1024_t y = from_uint(4294967291);
    for (int i = 0; i < 2; i++) {
        x = add_op(x, x);
        x = add_op(x, from_uint(i));
    }

    for (int i = 0; i < 2; i++) {
        y = add_op(y, y);
        y = add_op(y, from_uint(i));
    }

    printf_value(x);
    printf_value(y);
    printf_value(mult_op(x, y));

    uint1024_t g;
    scanf_value(&g);
    printf_value(g);
    return 0;
}