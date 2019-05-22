#include "frac.h"



int main(int argc, char const *argv[]) {

    // test :
    // on essaie de calculer 2/3 avec plein de décimales
    frac f1 = frac_calcul(2, 3);

    // on fais la même pour 1/3
    frac f2 = frac_calcul(1, 3);
    // on additionne les deux pour avoir 1 ??


    frac_free(f1);
    frac_free(f2);

    return 0;
}
