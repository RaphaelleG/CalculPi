#!/usr/bin/python3

from decimal import *


def get_tupple(n):
    a = (-1)**n *(4*239**(2*n+1) - 5**(2*n+1))
    b = (5*239)**(2*n+1)*(2*n+1)

    return (a,b)


def is_eq(k, m):
    t = get_tupple(k+1);
    res = Decimal(t[0])/(Decimal(t[1]))

    res = Decimal(res)*Decimal(4)/Decimal(3.15)

    return Decimal(res).compare(Decimal(10) ** Decimal(-m));


def get_N(m):
    n=1

    while ( is_eq(n,m) == 1):
        n = n*10

    min = n
    max = n*10
    while(min < max):
        print("min = ",min)
        print("max = ", max)

        n = int ((min+max)/2)
        print("n = ", n)
        t = is_eq(n, m)
        print(t)
        print("\n")
        if (t == 1):
            min = n +1
        elif (t == 0):
            break
        else:
            max = n-1
    return n


def get_array_formula_pi(lim):
    a = []
    for i in range(0, lim):
        a.append(get_tupple(i))
    return (a)




def main():
    print("COUCOU")
    getcontext().prec = 105

    lim = get_N(100)
    print (lim)

    tab = get_array_formula_pi(lim)
    frac = []

    for i in tab:
        frac.append(Decimal(i[0])/Decimal(i[1]))

    my_pi = 0
    for j in frac:
        my_pi = Decimal(my_pi)+Decimal(j)

    my_pi = Decimal(my_pi)*Decimal(4)

    print(my_pi)


main()
