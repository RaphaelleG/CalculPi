#include "utils.h"


int     mx(int m1, int m2)
{
    return ((m1 >= m2)? m1: m2);
}

int     mn(int m1, int m2)
{
    return ((m1 >= m2)? m2:m1);
}


int     dichoto(int n, big_int f, int i)
{
    int c = 5;
    int a = 0;
    int b = 10;
    big_int k = bi_int_to_bi(n);
    for (size_t l = 0; l < f.taille; l++)
    {
        k = bi_case_en_plus(k);
    }
    big_int zeros = bi_alloc(f.taille);
    big_int j = bi_minus(k,  bi_fois_by_int(f, c));
    while ( bi_is_eq(j, zeros) == 0 )
    {
        if (bi_is_sup(j, zeros) == 1)
        {
            a = c;
            c = (a+b)/2;
        }
        else
        {
            b = c;
            c = (a+b)/2;
        }
    }
    return c;
}
