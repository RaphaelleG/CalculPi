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


big_int             bi_case_en_plus(big_int f)
{
    big_int f2 = bi_alloc(f.taille +1);
    for (size_t i = 0; i < f.taille; i++) {
        f2.nombre[i] = f.nombre[i];
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


big_int             bi_add(big_int f1, big_int f2)
{
    big_int res = bi_alloc(f1.taille +1);
    int retenue = 0;
    for (size_t i = 0; i < res.taille-1; i++)
    {
        int k = res.taille -1 -i;
        res.nombre[k] = f1.nombre[k-1] + f2.nombre[k-1] + retenue;
        if (res.nombre[k] < 0)
        {
            retenue = 1;
            res.nombre[k]-= LIM;
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
    big_int res = bi_alloc(f1.taille+1);
    int retenue = 0;
    for (size_t i = 0; i < f1.taille ; i++)
    {
        int j = res.taille-1 -i;
        res.nombre[j] = f1.nombre[j-1];
        if (f1.nombre[j-1] < f2.nombre[j-1])
        {
            retenue = 1;
            res.nombre[j] = 10*f1.nombre[j-1];
            // on ne gère pas le dépassement pour l'instant
            // si c'est plus grand que LIM ça ne marche pas
            // Il faut trouver un autre moyen de le calculer
        }
        res.nombre[j] -= f2.nombre[j-1] + retenue;
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


big_int             bi_div_by_int(big_int f, int n);

big_int             bi_calcul(int num, int den)
{
    // res [0, 0,... , 0]
    big_int res = bi_alloc(TAILLE);
    big_int x = bi_int_to_bi(num*MULT);
    // tmp = [0] au début
    big_int tmp = bi_alloc(1);
    // tmp2 = den * tmp
    big_int tmp2;

    for (size_t i = 0; i < res.taille; i++)
    {

        printf("tmp = " );
        bi_print(tmp);
        printf("x = " );
        bi_print(x);

        tmp2 = bi_fois_by_int(tmp, den);

        printf("tmp2 = " );
        bi_print(tmp2);

        big_int f = bi_minus(x, tmp2);
        printf("calcul f ... " );
        bi_print(f);

        if (i == 0)
            res.nombre[i] = f.nombre[0]/den;
        else
            res.nombre[i] = f.nombre[i-1] * MULT/den ;

        x = bi_case_en_plus(x);

        tmp = bi_case_en_plus(tmp);
        tmp.nombre[i] = res.nombre[i];

        printf("\n" );
    }
    return res;
}



void                bi_print(big_int f)
{
    for (size_t i = 0; i < f.taille; i++) {
        printf("%d  ", f.nombre[i]);
    }
    printf("\n");
}
