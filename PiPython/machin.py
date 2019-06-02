#!/usr/bin/python3

from decimal import *
import time
import math


def show_progress_bar(bar_length, completed, total):
	bar_length_unit_value = (total / bar_length)
	completed_bar_part = math.ceil(completed / bar_length_unit_value)
	progress = "*" * completed_bar_part
	remaining = " " * (bar_length - completed_bar_part)
	percent_done = "%.2f" % ((completed / total) * 100)

	text = f' [{progress}{remaining}] {percent_done}%'
	if completed != total:
		print(text, end='\r')
	else:
		print(text)


def get_tupple(n):
	a = (-1)**n *(4*239**(2*n+1) - 5**(2*n+1))
	b = (5*239)**(2*n+1)*(2*n+1)

	return (a,b)


def is_eq(k, m):
	t = get_tupple(k+1);
	res = Decimal(t[0])/(Decimal(t[1]))

	res = Decimal(res)*Decimal(4)/Decimal(3.15)

	cmp = Decimal(10)**Decimal(-m)

	t = Decimal(res).compare_total_mag(Decimal(cmp));
	return t


def get_N(m):
	n=1
	# Pour trouver l'ordre de grandeur du n
	while (is_eq(n*10, m) == 1):
		n *= 10

	min = n
	max = n*10
	# Pour trouver précisement le n
	while(min < max):
		n = int ((min+max)/2)
		t = is_eq(n, m)

		if (t == 1):
			min = n +1
		elif (t == 0):
			break
		else:
			max = n-1
	return n


def get_pi(lim):
	pi = Decimal(0)
	print("Calcul de pi :")
	for i in range(0, lim):
		b = get_tupple(i)
		pi = pi + Decimal(b[0])/Decimal(b[1])
		show_progress_bar(30, i+1, lim)
	pi = pi * Decimal(4)
	return (pi)




def main():
	print("Combien de décimales voulez vous ? ")
	nb_dec = input()
	t1 = time.time()
	nb_dec = int(nb_dec)

	nb_dec = nb_dec +1
	getcontext().prec = nb_dec

	lim = get_N(nb_dec)
	print (lim)

	my_pi = get_pi(lim+5)

	print(my_pi)
	print('temps de calcul = {0} secondes'.format(time.time()-t1))

if __name__ == '__main__':
	main()
