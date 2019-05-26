#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "big_int.h"


int main(int argc, char const *argv[]) {

    // int a = 2147483640;
    // int b = 27;
    // printf("%d\n", a+b);
    // printf("%d\n", a+b);
    //
    //
    // printf("%d\n", a+b+LIM);
    big_int test = bi_calcul(1, 7);
    bi_print(test);
    bi_free(test);

    return 0;
}
