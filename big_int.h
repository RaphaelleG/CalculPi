#ifndef big_int_H
#define big_int_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define TAILLE  4
#define MULT    1e8
#define LIM     2147483647
// si bug de calcul chelou, penser à + ou - 1 dans les calculs


typedef struct      big_int {
    uint8_t         taille;
    int             *nombre;
}                   big_int;


big_int             bi_alloc(uint8_t taille);
void                bi_free(big_int f);

big_int             bi_int_to_bi(int n);
// sert à ajouter une case à la fin avec un 0 dedans
big_int             bi_case_en_plus(big_int f);
// sert à enlever une case au début qui vaut 0
big_int             bi_case_en_moins(big_int f);

// addition et soustraction de deux big_int de la même taille
// Pensez peut être a une amélioration avec possibilité d'avoir 2 tailles différentes
big_int             bi_add(big_int f1, big_int f2);
big_int             bi_minus(big_int f1, big_int f2);
big_int             bi_fois_by_int(big_int f, int n);
big_int             bi_div_by_int(big_int f, int n);


big_int             bi_calcul(int num, int den);
void                bi_print(big_int f1);



#endif
