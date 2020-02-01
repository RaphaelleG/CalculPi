#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "big_int.h"

void        machin();
int main(int argc, char const *argv[]) {

    // big_int *test = bi_calcul(1, 10, 9);
    big_int *test = bi_calcul(1,7,1);
    bi_print(test);
    bi_free(test);

    // big_int testpow = bi_int_pow_to_bi(2, 64);
    // bi_print(testpow);
    // bi_free(testpow);

    //machin();

    return 0;
}
