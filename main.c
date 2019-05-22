#include "frac.h"



int main(int argc, char const *argv[]) {

    frac f = frac_calcul(2, 3);
    frac_free(f);
    return 0;
}
