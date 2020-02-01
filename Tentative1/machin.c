#include "big_int.h"



void        machin()
{
    big_int *tab1[2], *tab2[2];
    tab1[0] = bi_calcul(1,5,1);
    tab1[1] = bi_calcul(1,5,3);
    tab2[0] = bi_calcul(1,239,1);
    tab2[1] = bi_calcul(1,239,3);
    big_int *res1 = bi_minus(tab1[0], tab1[1]);
    big_int *res2 = bi_minus(tab2[0], tab2[1]);
    bi_free(tab1[0]);
    bi_free(tab1[1]);
    bi_free(tab2[0]);
    bi_free(tab2[1]);

    res1 = bi_fois_by_int(res1, 4);
    big_int *res = bi_minus(res1, res2);
    res = bi_fois_by_int(res, 4);
    bi_print(res);
    bi_free(res);
    bi_free(res1);
    bi_free(res2);

}
