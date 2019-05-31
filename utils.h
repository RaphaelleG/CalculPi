#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "big_int.h"

int     mx(int m1, int m2);
int     mn(int m1, int m2);

int     dichoto(int n, big_int f, int i);

#endif
