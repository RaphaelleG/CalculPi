#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>



int main(int argc, char const *argv[]) {

    int a = 2147483640;
    int b = 27;
    printf("%d\n", a+b);
    printf("%d\n", a+b);


    printf("%d\n", a+b+LIM);

    return 0;
}
