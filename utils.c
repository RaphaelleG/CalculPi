#include "utils.h"


int     mx(int m1, int m2)
{
    return ((m1 >= m2)? m1: m2);
}

int     mn(int m1, int m2)
{
    return ((m1 >= m2)? m2:m1);
}


int     dichoto(int n, big_int *f, int m)
{
    int c;
    int a = 0;
    int b = 9;

    big_int *k = bi_int_to_bi(n);
    big_int *zeros = bi_alloc(f->taille);

    while (a!=b)
    {
        c = (a+b) /2;
        big_int *l = bi_fois_by_int(f, m+c);
        big_int *j = bi_minus(k,l);
        if(bi_is_eq(j, zeros)==1)
        {
            bi_free(j);
            bi_free(l);
            break;
        }

        if (bi_is_sup(j, zeros) == 1)
            a = c+1;
        else
            b = c-1;
        bi_free(j);
        bi_free(l);
    }
    if(a==b)
        c=a;
    bi_free(zeros);
    bi_free(k);



    return c;
}
