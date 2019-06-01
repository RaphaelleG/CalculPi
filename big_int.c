#include "big_int.h"
#include "utils.h"



big_int*             bi_alloc(uint8_t taille)
{
    int * nombre = (int *) malloc(taille *sizeof(int));
    if( nombre == NULL)
        return NULL;
    big_int *f = malloc(sizeof(big_int));
    f->taille = taille;
    f->nombre = nombre;
    for (size_t i = 0; i < f->taille; i++) {
        f->nombre[i] = 0;
    }
    return f;
}
void                bi_free(big_int *f)
{
    free(f->nombre);
    free(f);
}



big_int*             bi_int_to_bi(int n)
{
    big_int *f = bi_alloc(1);
    f->nombre[0] = n;
    return f;
}
big_int*             bi_int_pow_to_bi(int x, int n)
{
    big_int *res = bi_int_to_bi(x);
    for (size_t i = 1; i < n; i++)
        res = bi_fois_by_int(res, x);
    return res;
}



void             bi_case_en_plus(big_int *f)
{
    int * nombre = (int *) malloc((f->taille+1) * sizeof(int));

    for (size_t i = 0; i < f->taille; i++) {
        nombre[i] = f->nombre[i];
    }
    nombre[f->taille] = 0;
    free(f->nombre);
    f->taille +=1;
    f->nombre = nombre;

}

void             bi_case_au_debut(big_int *f)
{
    int *nombre = (int *) malloc((f->taille+1) * sizeof(int));

    nombre[0] = 0;
    for (size_t i = 0; i < f->taille; i++) {
        nombre[i+1] =f->nombre[i];
    }
    free(f->nombre);
    f->taille +=1;
    f->nombre = nombre;
}
void             bi_case_en_moins(big_int *f)
{
    int * nombre = (int *) malloc((f->taille-1) * sizeof(int));

    for (size_t i = 0; i < f->taille-1; i++) {
        nombre[i] = f->nombre[i+1];
    }

    free(f->nombre);
    f->taille -=1;
    f->nombre = nombre;
}



int                 bi_is_eq(big_int *f1, big_int *f2)
{
    bi_same_size(f1,f2);
    for (size_t i = 0; i < f1->taille; i++)
    {
        if (f1->nombre[i] != f2->nombre[i])
            return 0;
    }
    return 1;
}
int                 bi_is_sup(big_int *f1, big_int *f2)
{
    bi_same_size(f1,f2);
    for (size_t i = 0; i < f1->taille; i++)
    {
        if (f1->nombre[i] > f2->nombre[i])
            return 1;
        if (f1->nombre[i] < f2->nombre[i])
            return 0;
    }
    return 1;
}

void                bi_same_size(big_int *f1, big_int *f2)
{
    if (f1->taille != f2->taille)
    {
        if(f1->taille == mx(f1->taille, f2->taille))
        {
            int t = f1->taille-f2->taille;
            for (size_t i = 0; i < t; i++)
                bi_case_au_debut(f2);
        }
        else
        {
            int t = f2->taille-f1->taille;
            for (size_t i = 0; i < t; i++)
                bi_case_au_debut(f1);
        }
    }
}

big_int*             bi_add(big_int *f1, big_int *f2)
{
    bi_same_size(f1,f2);
    big_int *res = bi_alloc(f1->taille +1);
    int retenue = 0;

    for (size_t i = 0; i < res->taille-1; i++)
    {
        int k = res->taille -1 -i;
        res->nombre[k] = f1->nombre[k-1] + f2->nombre[k-1] + retenue;

        if (res->nombre[k] >= MULT)
        {
            retenue = 1;
            res->nombre[k] = res->nombre[k] % MULT;
        }
        else
            retenue = 0;

    }
    res->nombre[0] = retenue;

    if (retenue == 0)
        bi_case_en_moins(res);
    return res;
}



big_int*             bi_minus(big_int *f1, big_int *f2)
{
    bi_same_size(f1,f2);

    big_int *res = bi_alloc(f1->taille);
    int retenue = 0;
    for (int j = res->taille - 1; j >= 0; j--)
    {
        res->nombre[j] = f1->nombre[j];
        if (f1->nombre[j] < f2->nombre[j])
        {
            res->nombre[j] -= f2->nombre[j] + retenue;
            res->nombre[j] += MULT;
            retenue = 1;
        }
        else
        {
            res->nombre[j] -= f2->nombre[j] + retenue;
            retenue = 0;
        }
    }
    return res;
}



big_int*             bi_fois_by_int(big_int *f, int n)
{
    big_int *res = bi_alloc(f->taille);
    for (size_t i = 0; i < n; i++) {
        res = bi_add(res, f);
    }

    return res;
}
big_int*             bi_fois_by_bi(big_int *f1, big_int *f2)
{
    big_int **tmp = (big_int**) malloc(f2->taille*sizeof(big_int));

    for (size_t i = 0; i < f2->taille; i++) {
        tmp[i] = bi_fois_by_int(f1, f2->nombre[i]);
        for (size_t j = 0; j < i; j++)
            bi_case_en_plus(tmp[i]);
    }
    big_int *zeros = bi_alloc(f2->taille);
    for (size_t i = 0; i < f2->taille; i++) {
        zeros = bi_add(zeros, tmp[i]);
        bi_free(tmp[i]);
    }
    if (zeros->nombre[0] ==0)
        bi_case_en_moins(zeros);
    return zeros;
}



int                 bi_div_int_by_bi(int n, big_int *f)
{
    // On cherche c tel que n/(f.nombre[0] + ... +f.nombre[TAILLE-1])
    // c = c1c2c3c4c5c6c7c8
    int c = 0;
    int l = 1;
    for (size_t i = 0; i < 9; i++)
    {
        l *= 10;
        int m = n*l;
        printf("c = %d \n", c);
        c = l*c + dichoto(m, f, c*10);
        printf("test \n" );
    }
    return c;
}



big_int*             bi_calcul(int num, int den, int exp)
{
    // res [0, 0,... , 0]
    big_int *res = bi_alloc(TAILLE);
    big_int *x = bi_int_to_bi(num);
    big_int *y = bi_int_pow_to_bi(den, exp);
    y = bi_fois_by_int(y, exp);
    printf("y = ");
    bi_print(y);
    // tmp = [0] au début
    big_int *tmp = bi_alloc(1);
    // tmp2 = den * tmp
    big_int *tmp2;
    big_int *f;

    for (size_t i = 0; i < res->taille; i++)
    {
        printf("tour %ld\n",i );
        printf("tmp = " );
        bi_print(tmp);
        printf("x = " );
        bi_print(x);

        if (y->taille == 1)
            tmp2 = bi_fois_by_int(tmp, y->nombre[0]);
        else
            tmp2 = bi_fois_by_bi(tmp, y);

        printf("tmp2 = " );
        bi_print(tmp2);

        f = bi_minus(x, tmp2);
        printf("calcul f ... " );
        bi_print(f);

        if (i == 0)
        {
            if (y->taille == 1)
                res->nombre[i] = f->nombre[0] / y->nombre[0];
            else
            {
                printf("taille trop grande\n" );
                //res->nombre[i] = bi_div_int_by_bi(f->nombre[0], y);
            }
        }
        else
        {
            if (y->taille == 1)
                res->nombre[i] = f->nombre[i-1]* MULT/y->nombre[0];
            else
                printf("taille trop grande\n" );
                // res->nombre[i] =  bi_div_int_by_bi(f->nombre[i-1]*MULT, y);
        }

        bi_case_en_plus(x);

        bi_case_en_plus(tmp);
        tmp->nombre[i] = res->nombre[i];

        printf("\n" );
    }
    bi_free(x);
    bi_free(y);
    bi_free(tmp);
    bi_free(tmp2);
    bi_free(f);
    return res;
}



void                bi_print(big_int *f)
{
    for (size_t i = 0; i < f->taille; i++) {
        printf("%d  ", f->nombre[i]);
    }
    printf("\n");
}
