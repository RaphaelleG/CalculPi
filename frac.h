#ifndef FRAC_H
#define FRAC_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define TAILLE  10
#define MULT    1e9


typedef struct      frac {
    uint8_t         taille;
    int             *nombre;
}                   frac;


frac                frac_alloc(uint8_t taille);
void                frac_free(frac f);
frac                frac_add(frac f1, frac f2);
frac                frac_calcul(int num, int den);
void                frac_print(frac f1);



#endif
