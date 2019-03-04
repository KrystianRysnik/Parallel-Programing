#include <iostream>
#include <conio.h>
#include <time.h>
#include <math.h>

#define DICES 600
#define M_PI 3.14159265358979323846
#define M_E 2.71828182845904523536


using namespace std;

double logFromSterlingFormula(int N) {
	return log(pow(N / M_E, N) * sqrt(2 * M_PI * N));
}

void simulation(int number, int hits) {
	int dice[DICES];

	// Ustawienie kostek
	for (int i = 0; i < DICES; i++) 
	{
		dice[i] = number;
	}

	// Uderzenie
	for (int i = 0; i < hits; i++) 
	{
		for (int j = 0; j < DICES; j++) 
		{
			if (1 == rand() % 20 + 1)
			{
				dice[j] = rand() % 6 + 1;
			}
		}

		// Wczytanie kostek
		int count[6] = { 0, 0, 0, 0, 0, 0 };
		for (int nr = 0; nr < DICES; nr++)
		{
			count[dice[nr] - 1]++;
		}
		int sum = count[0] + count[1] + count[2] + count[3] + count[4] + count[5];
		cout << i+1 << ". [" << sum << "][" << count[0] << ", " << count[1] << ", " << count[2] << ", " << count[3] << ", " << count[4] << ", " << count[5] << "]" << endl;
		
		double sum2 = 1;
		for (int k = 0; k < 6; k++) {
			sum2 *= logFromSterlingFormula(count[k]);
		}

		double entriopia = logFromSterlingFormula(DICES) / sum2;
	
		
		cout << "Entriopia = " << entriopia << endl << "------------------------------" << endl;
	}
}

int main() {

	srand(time(NULL));

	// Ktorym oczkiem do gory
	int number = 6;
	// Liczba uderzen
	int hits = 100;
	/*
	 * Prawdopodobienstwo = 1/20
	 * Liczba oczek = 1/6
	 */

	simulation(number, hits);

	cout << "Test";
	_getch();
	return 0;
}