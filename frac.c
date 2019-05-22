#include "frac.h"
#include "utils.h"



frac                frac_alloc(uint8_t taille)
{
    int * nombre = (int *) malloc(taille *sizeof(int));
    if( nombre == NULL)
        printf("echec malloc frac\n" );
    frac f;
    f.taille = taille;
    f.nombre = nombre;
    return f;
}


void                frac_free(frac f)
{
    free(f.nombre);
}


frac                frac_add(frac f1, frac f2)
{
    uint8_t taille = mx(f1.taille, f2.taille) + 1;
    frac res = frac_alloc(taille);
    // Réflechir sur comment gérer les retenues !!!




    return res;
}


frac                frac_calcul(int num, int den){
    frac f = frac_alloc(TAILLE);

    // je suis pas sure de ça du tout ...
    unsigned long long int tmp = 0;
    unsigned long long int c;

    // Marche pas à partir de i=1 car tmp dépasse les entiers, d'ou mon test de unsigned long long mais ça marche pas mieux
    for (size_t i = 0; i < f.taille; i++) {
        int exp = my_pow(MULT, i+1);
        c = exp *(num - tmp*den) / den;
        tmp = MULT*tmp + f.nombre[i];
        f.nombre[i] = (int)c;
    }

    frac_print(f);
    return f;
}


void                frac_print(frac f)
{
    for (size_t i = 0; i < f.taille; i++) {
        printf("%d  ", f.nombre[i]);
    }
    printf("\n");
}
