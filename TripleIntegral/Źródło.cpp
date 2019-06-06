#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <math.h>

using namespace std;

// Wyrazenie
double expression(double x, double y, double z)
{
	// integrate (cos(x) * exp(-y) * log10(z)) / sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2) + 1) dx dy dz, x=-1..1, y=0..1, z=1..5
	return (cos(x) * exp(-y) * log10(z)) / sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2) + 1);
}

// Podwojna calka
double TripleIntegral(double lowerX, double upperX, double lowerY, double upperY, double lowerZ, double upperZ)
{
	double sum = 0;

	// Iloœæ prostok¹tów
	int n = 1000;

	// Krok
	double hx = (upperX - lowerX) / (double)n;
	double hy = (upperY - lowerY) / (double)n;
	double hz = (upperZ - lowerZ) / (double)n;

#pragma omp parallel for reduction(+ : sum)
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			for (int k = 1; k <= n; k++) 
			{
				sum += expression(lowerX + (i*hx), lowerY + (j*hy), lowerZ + (k*hz)) * hx * hy * hz;
			}
		}
	}
	double integral = sum;
	return integral;
}

int main()
{
	// Przedzia³y
	double xp = -1.0;
	double xk = 1.0;

	double yp = 0.0;
	double yk = 1.0;

	double zp = 1.0;
	double zk = 5.0;

	double calka = TripleIntegral(xp, xk, yp, yk, zp, zk);

	cout << "Wynik potrojnej calki metoda prostokatow: " << calka << endl;

	_getch();
	return 0;
}
