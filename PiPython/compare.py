#!/usr/bin/python3

from decimal import *
import numpy as np
import matplotlib.pyplot as plt

def fact(n, acc = 1) :
	for i in range(2, n):
		acc *= i
	return acc

#Série de Riemann
def get_tupple_r(k) :
	a = 1
	b = k**2
	return (a,b)

#Série de Riemann alterné
def get_tupple_ra(k):
	a = (-1)**(k+1)
	b = k**2
	return (a,b)

# Développement en série d'Arctan
def get_tupple_a(k):
	a = (-1)**k
	b = 2*k+1
	return(a,b)

# Formule de Machin
def get_tupple_m(n):
	a = (-1)**n *(4*239**(2*n+1) - 5**(2*n+1))
	b = (5*239)**(2*n+1)*(2*n+1)
	return (a,b)

# IN PROGRESS
# # Formule de Chudnovsky
# def get_tupple_chud(n) :
# 	a = (-1)**n * 12 * fact(6*n) * (13491409 + (545150134*n))
# 	b = (fact(3*n)) * (fact(n))**3 * (640320)**(3*n)
# 	return (a,b)

def get_array_r(lim):
	b = 0
	c = []
	for i in range(1,lim):
		a = get_tupple_r(i)
		b = Decimal(b) + (Decimal(6)*(Decimal(a[0])/ Decimal(a[1])))
		b2 = Decimal(b) ** Decimal('0.5')
		c.append(b2)
	return c;

def get_array_ra(lim):
	b = 0
	c = []
	for i in range(1,lim):
		a = get_tupple_ra(i)
		b = Decimal(b) + (Decimal(12)*(Decimal(a[0])/ Decimal(a[1])))
		b2 = Decimal(b) ** Decimal('0.5')
		c.append(b2)
	return c;

def get_array_a(lim, fct):
	b = 0
	c = []
	for i in range(0,lim):
		a = fct(i)
		b = Decimal(b) + ( Decimal(4) * (Decimal(a[0])/ Decimal(a[1])))
		c.append(b)
	return c;

#IN PROGRESS
# def get_array_chud(lim):
# 	b = 0
# 	c = []
# 	for i in range(0,lim):
# 		a = get_tupple_chud(i)
# 		b = Decimal(b) + (Decimal(1) * (Decimal(a[1])/ Decimal(a[0])))
# 		c.append(b)
# 	return c;

def main():
	lim = 100
	getcontext().prec = lim +2

	# calculer x décimales avec riemann
	res1 = get_array_r(lim+1)
	# calculer x décimales avec riemann alterné
	res2 = get_array_ra(lim+1)
	# calculer x décimales avec arctan
	res3 = get_array_a(lim, get_tupple_a)

	# calculer x decimales avec machin
	res4 = get_array_a(lim, get_tupple_m)

	# IN PROGRESS
	# calculer x decimales avec machin
	# res5 = get_array_chud(lim)


	# comparer les convergences
	x = range(0, lim)
	plt.plot(x, res1, label='Série de Riemann')
	plt.plot(x, res3, label='Série de Riemann alternée')
	plt.plot(x, res2, label='Développement d\'Arctan')
	plt.plot(x, res4, label='Formule de Machin')

	legend = plt.legend(loc='upper center', shadow=True, fontsize='x-large')

	plt.show()


if __name__ == '__main__':
	main()
