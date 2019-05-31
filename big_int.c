#include "big_int.h"
#include "utils.h"



big_int             bi_alloc(uint8_t taille)
{
    int * nombre = (int *) malloc(taille *sizeof(int));
    if( nombre == NULL)
        printf("echec malloc big_int\n" );
    big_int f;
    f.taille = taille;
    f.nombre = nombre;
    for (size_t i = 0; i < f.taille; i++) {
        f.nombre[i] = 0;
    }
    return f;
}
void                bi_free(big_int f)
{
    free(f.nombre);
}



big_int             bi_int_to_bi(int n)
{
    big_int f = bi_alloc(1);
    f.nombre[0] = n;
    return f;
}
big_int             bi_int_pow_to_bi(int x, int n)
{
    big_int res = bi_int_to_bi(x);
    for (size_t i = 1; i < n; i++)
        res = bi_fois_by_int(res, x);
    return res;
}



big_int             bi_case_en_plus(big_int f)
{
    big_int f2 = bi_alloc(f.taille +1);
    for (size_t i = 0; i < f.taille; i++) {
        f2.nombre[i] = f.nombre[i];
    }
    bi_free(f);
    return f2;
}
big_int             bi_case_au_debut(big_int f)
{
    big_int f2 = bi_alloc(f.taille +1);
    for (size_t i = 0; i < f.taille; i++) {
        f2.nombre[i+1] =f.nombre[i];
    }
    bi_free(f);
    return f2;
}
big_int             bi_case_en_moins(big_int f)
{
    big_int f2 =bi_alloc(f.taille-1);
    for (size_t i = 0; i < f2.taille; i++) {
        f2.nombre[i] = f.nombre[i+1];
    }
    bi_free(f);
    return f2;
}



int                 bi_is_eq(big_int f1, big_int f2)
{
    // on suppose f1.taille == f2.taille
    for (size_t i = 0; i < f1.taille; i++)
    {
        if (f1.nombre[i] != f2.nombre[i])
            return 0;
    }
    return 1;
}
int                 bi_is_sup(big_int f1, big_int f2)
{
    // on suppose f1.taille == f2.taille
    for (size_t i = 0; i < f1.taille; i++)
    {
        if (f1.nombre[i] > f2.nombre[i])
            return 1;
        if (f1.nombre[i] < f2.nombre[i])
            return 0;
    }
    return 1;
}



big_int             bi_add(big_int f1, big_int f2)
{
    if (f1.taille != f2.taille)
    {
        if(f1.taille == mx(f1.taille, f2.taille))
        {
            int t = f1.taille-f2.taille;
            for (size_t i = 0; i < t; i++)
                f2 = bi_case_au_debut(f2);
        }
        else
        {
            int t = f2.taille-f1.taille;
            for (size_t i = 0; i < t; i++)
                f1 = bi_case_au_debut(f1);
        }
    }

    big_int res = bi_alloc(f1.taille +1);
    int retenue = 0;

    for (size_t i = 0; i < res.taille-1; i++)
    {
        int k = res.taille -1 -i;
        res.nombre[k] = f1.nombre[k-1] + f2.nombre[k-1] + retenue;

        if (res.nombre[k] >= MULT)
        {
            retenue = 1;
            res.nombre[k] = res.nombre[k] % MULT;
        }
        else
            retenue = 0;

    }
    res.nombre[0] = retenue;
    if (retenue == 0)
        res = bi_case_en_moins(res);
    return res;
}



big_int             bi_minus(big_int f1, big_int f2)
{
    if (f1.taille != f2.taille)
    {
        if(f1.taille == mx(f1.taille, f2.taille))
        {
            for (size_t i = 0; i < f1.taille-f2.taille; i++)
                f2 = bi_case_au_debut(f2);
        }
        else
        {
            for (size_t i = 0; i < f2.taille-f1.taille; i++)
                f1 = bi_case_au_debut(f1);
        }
    }
    big_int res = bi_alloc(f1.taille+1);
    int retenue = 0;
    for (size_t i = 0; i < f1.taille ; i++)
    {
        int j = res.taille-1 -i;
        res.nombre[j] = f1.nombre[j-1];
        if (f1.nombre[j-1] < f2.nombre[j-1])
        {
            res.nombre[j] -= f2.nombre[j-1] + retenue;
            res.nombre[j] += MULT;
            retenue = 1;
        }
        else
        {
            res.nombre[j] -= f2.nombre[j-1] + retenue;
            retenue = 0;
        }

    }
    res.nombre[0] = retenue;
    if (retenue == 0)
        res = bi_case_en_moins(res);
    return res;

}



big_int             bi_fois_by_int(big_int f, int n)
{
    big_int res = bi_alloc(f.taille);
    for (size_t i = 0; i < n; i++) {
        res = bi_add(res, f);
    }

    return res;
}
big_int             bi_fois_by_bi(big_int f1, big_int f2)
{
    big_int * tmp = (big_int*) malloc(f2.taille*sizeof(big_int));
    for (size_t i = 0; i < f2.taille; i++) {
        tmp[i] = bi_fois_by_int(f1, f2.nombre[i]);
        for (size_t j = 0; j < i; j++)
            tmp[i] = bi_case_en_plus(tmp[i]);
    }
    big_int zeros = bi_alloc(f2.taille);
    for (size_t i = 0; i < f2.taille; i++) {
        zeros = bi_add(zeros, tmp[i]);
        bi_free(tmp[i]);
    }
    return zeros;
}



int                 bi_div_int_by_bi(int n, big_int f)
{
    // On cherche c tel que n/(f.nombre[0] + ... +f.nombre[TAILLE-1])
    // c = c1c2c3c4c5c6c7c8
    int c = 0;
    int k = 0, l = 0;
    for (size_t i = 0; i < 9; i++)
    {
        k = 8-i;
        l = pow(10, k);
        c = c + l*dichoto(n, f, i);
    }
    return c;
}



big_int             bi_calcul(int num, int den, int exp)
{
    // res [0, 0,... , 0]
    big_int res = bi_alloc(TAILLE);
    big_int x = bi_int_to_bi(num);
    big_int y = bi_int_pow_to_bi(den, exp);
    printf("y = ");
    bi_print(y);
    // tmp = [0] au début
    big_int tmp = bi_alloc(1);
    // tmp2 = den * tmp
    big_int tmp2;
    big_int f;

    for (size_t i = 0; i < res.taille; i++)
    {
        printf("tour %ld\n",i );
        printf("tmp = " );
        bi_print(tmp);
        printf("x = " );
        bi_print(x);

        // if (y.taille == 1)
        //     tmp2 = bi_fois_by_int(tmp, y.nombre[0]);
        // else
        tmp2 = bi_fois_by_bi(tmp, y);

        printf("tmp2 = " );
        bi_print(tmp2);

        f = bi_minus(x, tmp2);
        printf("calcul f ... " );
        bi_print(f);

        if (i == 0)
        {
            if (y.taille ==1)
                res.nombre[i] = f.nombre[0]/y.nombre[0];
            else
            {
                res.nombre[i] = bi_div_int_by_bi(f.nombre[0], y);
            }
        }
        else
        {
            if (y.taille == 1)
                res.nombre[i] = f.nombre[i-1]* MULT/y.nombre[0];
            else
                res.nombre[i] =  bi_div_int_by_bi(f.nombre[i-1], y);
        }

        x = bi_case_en_plus(x);

        tmp = bi_case_en_plus(tmp);
        tmp.nombre[i] = res.nombre[i];

        printf("\n" );
    }
    bi_free(x);
    bi_free(tmp);
    bi_free(tmp2);
    bi_free(f);
    return res;
}



void                bi_print(big_int f)
{
    for (size_t i = 0; i < f.taille; i++) {
        printf("%d  ", f.nombre[i]);
    }
    printf("\n");
}
