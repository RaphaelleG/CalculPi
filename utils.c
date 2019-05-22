#include "utils.h"


uint8_t     mx(uint8_t m1, uint8_t m2)
{
    return ((m1 >= m2)? m1: m2);
}

int         my_pow(int x, size_t n)
{
    int res = 1;
    for (size_t i = 0; i < n; i++) {
        res = res*x;
    }
    return res;
}