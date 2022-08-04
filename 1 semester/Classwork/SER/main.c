#include <stdio.h>
#include <math.h>

double f(double x)
{
	double u, s;
	int i;
	s = 0;
	i = 1;
	u = x * x;
	s += u;
	do
	{
		u *= (-4 * x * x) / ((2.0 * i + 1) * (2.0 * i + 2));
		s += u;
		i++;
	} while (s + u != s);
	return s;
}

double g(double x)
{
	return sin(x) * sin(x);
}

void print_table(double a, double b, int m)
{
	int i = 0;
	double d;
	d = (b - a) / (double)(m - 1.0);
	printf("+-------+-------+----------+----------+-----------------+\n");
	printf("|   i   |   x   |   f(x)   |   g(x)   |   f(x) - g(x)   |\n");
	printf("+-------+-------+----------+----------+-----------------+\n");
	for (; i < m; i++)
	{
		printf("|%4d   |%6.2lf |%7.2lf   |%7.2lf   |%12.2le     |\n", i, a, f(a), g(a), fabs(f(a) - g(a)));
		printf("+-------+-------+----------+----------+-----------------+\n");
		a += d;
	}
}

int main(void)
{
	double a, b;
	int m;
	do
	{
		printf("Enter the first border (a): ");
		scanf_s("%lf", &a);
	} while (fabs(a) > 1);
	do
	{
		printf("Enter the first border (b): ");
		scanf_s("%lf", &b);
	} while (fabs(b) > 1);
	do
	{
		printf("Enter the number of lines(m): ");
		scanf_s("%d", &m);
	} while (m <= 1);
	print_table(a, b, m);
	return 0;
}

