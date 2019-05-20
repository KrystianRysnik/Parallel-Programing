#include <iostream>
#include <conio.h>
#include <time.h>
#include <math.h>

#define DICES 600
#define M_PI 3.14159265358979323846


using namespace std;

void czekaj(int milis);
void simulation(int number, int hits);

int main() {
	srand(time(NULL));

	float pocz;

	// Ktorym oczkiem do gory
	int number = 6;
	// Liczba uderzen
	int hits = 100;
	/*
	 * Prawdopodobienstwo = 1/20
	 * Liczba oczek = 1/6
	 */
	pocz = clock();

	simulation(number, hits);

	cout << "Czas trwania operacji calkowania : " << (clock() - pocz) << endl;

	_getch();
	return 0;
}

void czekaj(int milis) {
	time_t koniec;
	koniec = clock() + milis;
	while (koniec > clock()) {};
}

void simulation(int number, int hits) {
	int dice[DICES];

	// Ustawienie kostek
#pragma omp parallel for
	for (int i = 0; i < DICES; i++)
	{
		dice[i] = number;
	}

	// Uderzenie
	for (int i = 0; i < hits; i++)
	{
		czekaj(500);
#pragma omp parallel for
		for (int j = 0; j < DICES; j++)
		{
			if (1 == rand() % 20 + 1)
			{
				dice[j] = rand() % 6 + 1;
			}
		}

		// Wczytanie kostek
		int meshSum[] = { 0, 0, 0, 0, 0, 0 };
		int sum = 0;

#pragma omp parallel for
		for (int nr = 0; nr < DICES; nr++)
		{
#pragma omp critical
			meshSum[dice[nr] - 1]++;
		}
		sum = meshSum[0] + meshSum[1] + meshSum[2] + meshSum[3] + meshSum[4] + meshSum[5];
			
		
		// Liczenie entriopii
		double entropy = (DICES * log(DICES) - DICES) + 0.5*log(2 * M_PI * DICES);
#pragma omp parallel for reduction(- : entropy)
		for (int k = 0; k < 6; k++)
		{
			if (meshSum[k] != 0)
			{
				entropy -= (meshSum[k] * log(meshSum[k]) - meshSum[k]) + 0.5*log(2 * M_PI * meshSum[k]);
			}
		}

		cout << i + 1 << ". [" << sum << "][" << meshSum[0] << ", " << meshSum[1] << ", " << meshSum[2] << ", " << meshSum[3] << ", " << meshSum[4] << ", " << meshSum[5] << "]";
		cout << ", \tEntriopia = " << entropy << endl;
	}
}