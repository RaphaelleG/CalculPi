#!/usr/bin/python3

from decimal import *
import numpy as np
import matplotlib.pyplot as plt

def get_tupple_r(k):
    a = 1
    b = k**2
    return (a,b)

def get_tupple_ra(k):
    a = (-1)**(k+1)
    b = k**2
    return (a,b)

def get_tupple_a(k):
    a = (-1)**k
    b = 2*k+1
    return(a,b)

def get_array_r(lim):
    a = []
    b = 0
    c = []
    a.append((0,0))
    for i in range(1,lim):
        a.append(get_tupple_r(i))
        b = Decimal(b) + (Decimal(6)*(Decimal(a[i][0])/ Decimal(a[i][1])))
        b2 = Decimal(b) ** Decimal('0.5')
        c.append(b2)
    return c;

def get_array_ra(lim):
    a = []
    b = 0
    c = []
    a.append((0,0))
    for i in range(1,lim):
        a.append(get_tupple_ra(i))
        b = Decimal(b) + (Decimal(12)*(Decimal(a[i][0])/ Decimal(a[i][1])))
        b2 = Decimal(b) ** Decimal('0.5')
        c.append(b2)
    return c;

def get_array_a(lim):
    a = []
    b = 0
    c = []
    for i in range(0,lim):
        a.append(get_tupple_a(i))
        b = Decimal(b) + (Decimal(a[i][0])/ Decimal(a[i][1]))
        c.append(b)
    return c;


def main():
    lim = 100
    getcontext().prec = lim +2

    # calculer x décimales avec riemann
    res1 = get_array_r(lim+1)
    # calculer x décimales avec riemann alterné
    res2 = get_array_ra(lim+1)
    # calculer x décimales avec arctan
    res3 = get_array_a(lim)

    # comparer les convergences
    x = range(0, lim)
    plt.plot(x, res1)
    plt.plot(x, res2)
    plt.plot(x, res3)

    plt.show()




main()
