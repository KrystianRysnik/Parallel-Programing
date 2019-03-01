#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <math.h>

using namespace std;

double stepsize = 0.001;

// Wyrazenie
double expression(double x, double y) 
{ 
	return exp(-sqrt(x*x + y*y)) / (x*x + y*y);;
}

// Podwojna calka
double doubleIntegral(double lowerX, double upperX, double lowerY, double upperY)
{
	double sum = 0;

	for (double i = lowerX; i <= upperX; i += stepsize)
	{
		for (double j = lowerY; j <= upperY; j += stepsize)
		{
			sum += expression(i, j);
		}
	}
	double integral = sum * stepsize * stepsize;
	return integral;
}

int main()
{
	double xp = 1.0;
	double xk = 2.0;

	double yp = 1.0;
	double yk = 2.0;

	double calka = doubleIntegral(xp, xk, yp, yk);

	cout << "Wynik podwojnej calki metoda prostokatow: " << calka << endl;

	_getch();
	return 0;
}
