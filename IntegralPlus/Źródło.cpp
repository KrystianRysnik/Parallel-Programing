#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <math.h>

using namespace std;

// Wyrazenie
double expression(double x, double y)
{
	return exp(-sqrt(x*x + y * y)) / (x*x + y * y);;
}

// Podwojna calka
double doubleIntegral(double lowerX, double upperX, double lowerY, double upperY)
{
	double sum = 0, temp = 0;

	// Iloœæ prostok¹tów
	int n = 10000;

	// Krok
	double hx = (upperX - lowerX) / (double)n;
	double hy = (upperY - lowerY) / (double)n;

#pragma omp parallel sections private(temp)
	{
#pragma omp section
		{
			temp = 0;
			for (int i = 1; i <= n; i += 4)
			{
				for (int j = 1; j <= n; j++)
				{
					temp = expression(lowerX + (i*hx), lowerY + (j*hy)) * hx * hy;
#pragma omp critical
					sum += temp;
				}
			}
		}
#pragma omp section
		{
			temp = 0;
			for (int i = 2; i <= n; i += 4)
			{
				for (int j = 1; j <= n; j++)
				{
					temp = expression(lowerX + (i*hx), lowerY + (j*hy)) * hx * hy;
#pragma omp critical
					sum += temp;
				}
			}
		}
#pragma omp section
		{
			temp = 0;
			for (int i = 3; i <= n; i += 4)
			{
				for (int j = 1; j <= n; j++)
				{
					temp = expression(lowerX + (i*hx), lowerY + (j*hy)) * hx * hy;
#pragma omp critical
					sum += temp;
				}
			}
		}
#pragma omp section
		{
			temp = 0;
			for (int i = 4; i <= n; i += 4)
			{
				for (int j = 1; j <= n; j++)
				{
					temp = expression(lowerX + (i*hx), lowerY + (j*hy)) * hx * hy;
#pragma omp critical
					sum += temp;
				}
			}
		}
	}
	double integral = sum;
	return integral;
}

int main()
{
	// Przedzia³y
	double xp = 1.0;
	double xk = 2.0;

	double yp = 1.0;
	double yk = 2.0;

	double calka = doubleIntegral(xp, xk, yp, yk);

	cout << "Wynik podwojnej calki metoda prostokatow: " << calka << endl;

	_getch();
	return 0;
}
