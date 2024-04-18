#include "Math.h"
#include <cstdarg> ///pt functiile va_start ....
#include <cstdlib> ///fct atoi ...(pt convertiri)

int Math::Add(int a, int b) 
{
	return a + b;
}

int Math::Add(int a, int b, int c) 
{
	return a + b + c;
}

int Math::Add(double a, double b) 
{
	return (int)(a + b);
}

int Math::Add(double a, double b, double c) 
{
	return (int)(a + b + c);
}

int Math::Mul(int a, int b)
{
	return a * b;
}

int Math::Mul(int a, int b, int c) 
{
	return a * b * c;
}

int Math::Mul(double a, double b)
{
	return (int)(a * b);
}

int Math::Mul(double a, double b, double c) 
{
	return (int)(a * b * c);
}

int Math::Add(int count, ...) // sums up a list of integers
{
	va_list arg; ///lista argumentelor variabile
	va_start(arg, count);///lista arg cu count argumente variabile
	int sum = 0;///calculam suma (in int) a argumentelor variabile
	for (int i = 1; i <= count; ++i)
		sum += va_arg(arg, int);///adunam la suma argumentul curent din lista arg de tip int
	va_end(arg);///termina folosirea listei de argumente
	return sum;
}

char* Math::Add(const char* s1, const char* s2)
{
	if (s1 == nullptr || s2 == nullptr) return nullptr; ///verificam daca adunarea e posibile
	int x1 = atoi(s1);///convertim s1 in int
	int x2 = atoi(s2);///convertim s2 in int
	x1 += x2;///facem suma
	int aux = x1, ct = 0;///numaram cate cifre are x1
	while (aux != 0)
	{
		ct++;
		aux /= 10;
	}
	char* rez = new char[ct + 1]; ///declaram sirul rezultat
	for (int i = ct - 1; i >= 0; i--)
	{
		rez[i] = char('0' + (x1 % 10));
		x1 /= 10;
	}
	rez[ct] = NULL;
	return rez;
}