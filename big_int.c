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
    f.nombre[i] = n;

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
    int retenue =0;
    for (size_t i = res.taille-1; i > 0; i--)
    {
        res.nombre[i] = f1.nombre[i] + f2.nombre[i] + retenue;
        if (res.nombre[i] <= 0)
        {
            retenue = 1;
            res.nombre[i]-= LIM;
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
    big_int res = bi_alloc(f1.taille);
    for (size_t i = f.taille-1; i > -1; i--)
    {
        res.nombre[i] = mx(f1.nombre[i], f2.nombre[i]) - mn(f1.nombre[i], f2.nombre[i]);
    }
    return res;

}


// je crois que ça marche mais je ne suis pas sûre ...
big_int             bi_fois_by_int(big_int f, int n)
{
    big_int res = bi_alloc(f.taille +1);
    retenue = 0;
    for (size_t i = res.taille-1; i >0; i++) {
        res.nombre[i] = retenue;
        retenue = 0;
        for (size_t j = 0; j < n; j++) {
            res.nombre[i]+= f.nombre[i];
            if (res.nombre[i]<= 0)
            {
                retenue ++;
                res.nombre -= LIM;
            }
        }
    }
    res.nombre[0] = retenue;
    if (retenue == 0)
        res = bi_case_en_moins(res);
    return res;
}


big_int             bi_div_by_int(big_int f, int n);

big_int             bi_calcul(int num, int den);



void                bi_print(big_int f1)
{
    for (size_t i = 0; i < f.taille; i++) {
        printf("%d  ", f.nombre[i]);
    }
    printf("\n");
}
