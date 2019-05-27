#ifndef big_int_H
#define big_int_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define TAILLE  10
#define MULT    100000000
#define LIM     2147483647
// si bug de calcul chelou, penser à + ou - 1 dans les calculs


typedef struct      big_int {
    uint8_t         taille;
    int             *nombre;
}                   big_int;

// Pour créer un nouveau big_int et l'effacer à la fin
big_int             bi_alloc(uint8_t taille);
void                bi_free(big_int f);

// Pour convertir un entier simple en big_int,
// on fait juste un tableau à une case qui vaut n
big_int             bi_int_to_bi(int n);

// sert à ajouter une case à la fin avec un 0 dedans
// plus ou moins équivalent à faire *10^9
big_int             bi_case_en_plus(big_int f);

// sert à enlever une case au début qui vaut 0
big_int             bi_case_en_moins(big_int f);


// addition et soustraction de deux big_int de la même taille
// Pensez peut être a une amélioration avec possibilité d'avoir 2 tailles différentes ? Même si pas nécessaire
big_int             bi_add(big_int f1, big_int f2);
// Probleme avec la soustraction ou les retenues sont mal géré et ou on a des dépassement d'entier
big_int             bi_minus(big_int f1, big_int f2);

big_int             bi_fois_by_int(big_int f, int n);
// Pas ecrite car pas utile en fait, je sais pas si elle servira
big_int             bi_div_by_int(big_int f, int n);

// obtenir un decimales avec autant de décimales qu'on veut
big_int             bi_calcul(int num, int den);
void                bi_print(big_int f1);



#endif
