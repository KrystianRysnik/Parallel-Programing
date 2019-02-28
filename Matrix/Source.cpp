#include <conio.h>
#include <iostream>
#include <omp.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MATRIX_SIZE 2

using namespace std;

double matrixA[MATRIX_SIZE][MATRIX_SIZE];
double matrixB[MATRIX_SIZE][MATRIX_SIZE];
double matrixC[MATRIX_SIZE][MATRIX_SIZE];
double matrixD[MATRIX_SIZE][MATRIX_SIZE];

double tempA[MATRIX_SIZE][MATRIX_SIZE];
double tempB[MATRIX_SIZE][MATRIX_SIZE];

double resultA[MATRIX_SIZE][MATRIX_SIZE];
double resultB[MATRIX_SIZE][MATRIX_SIZE];
double resultC[MATRIX_SIZE][MATRIX_SIZE];

void multiplyMatrix(double matrixA[MATRIX_SIZE][MATRIX_SIZE], double matrixB[MATRIX_SIZE][MATRIX_SIZE], double resutlMatrix[MATRIX_SIZE][MATRIX_SIZE]);
bool checkMatrix(double matrixA[MATRIX_SIZE][MATRIX_SIZE], double matrixB[MATRIX_SIZE][MATRIX_SIZE], double matrixC[MATRIX_SIZE][MATRIX_SIZE]);

int main() {
	srand(time(NULL));

	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			matrixA[i][j] = (rand() % 20)*0.1234 + 1.111;
			matrixB[i][j] = (rand() % 20)*0.345 + 1.333;;
			matrixC[i][j] = (rand() % 20)*0.1234 + 1.111;;
			matrixD[i][j] = (rand() % 20)*0.345 + 1.333;;
		}
	}

	// resultA = (A * B) * (C * D)
	multiplyMatrix(matrixA, matrixB, tempA);
	multiplyMatrix(matrixC, matrixD, tempB);
	multiplyMatrix(tempA, tempB, resultA);

	// resultB = ((A * B) * C) * D
	multiplyMatrix(matrixA, matrixB, tempA);
	multiplyMatrix(tempA, matrixC, tempB);
	multiplyMatrix(tempB, matrixD, resultB);

	// resultC = A * ((B * C) * D)
	multiplyMatrix(matrixB, matrixC, tempA);
	multiplyMatrix(tempA, matrixD, tempB);
	multiplyMatrix(matrixA, tempB, resultC);

	if (checkMatrix(resultA, resultB, resultC))
	{
		cout << "Macierze A, B i C sa takie same!";
	}
	else
	{
		cout << "Macierza A, B i C sa rozne!";
	}

	_getch();
	return 0;
}

void multiplyMatrix(double matrixA[MATRIX_SIZE][MATRIX_SIZE], double matrixB[MATRIX_SIZE][MATRIX_SIZE], double resutlMatrix[MATRIX_SIZE][MATRIX_SIZE]) {
	for (int i = 0; i < MATRIX_SIZE; i++) {
		for (int j = 0; j < MATRIX_SIZE; j++) {
			resutlMatrix[i][j] = 0;
			for (int k = 0; k < MATRIX_SIZE; k++) {
				resutlMatrix[i][j] += matrixA[i][k] * matrixB[k][j];
			}
		}
	}
}

bool checkMatrix(double matrixA[MATRIX_SIZE][MATRIX_SIZE], double matrixB[MATRIX_SIZE][MATRIX_SIZE], double matrixC[MATRIX_SIZE][MATRIX_SIZE]) {
	bool same = true;
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			if (trunc(1000. * matrixA[i][j]) != trunc(1000. * matrixB[i][j])
				|| trunc(1000. * matrixB[i][j]) != trunc(1000. * matrixC[i][j]))
			{
				same = false;
			}
		}
	}
	return same;
}

