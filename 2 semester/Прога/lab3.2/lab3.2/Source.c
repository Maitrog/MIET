#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>

#define N 10
#define M 10

void getArr(int A[N][M])
{
	time_t k;
	srand(time(&k));
	int minus = 1;
	for (int i = 0; i < N; i++)
		for(int j = 0; j < M; j++)
		{
			minus = rand();
			A[i][j] = rand() % 10 * (minus % 2 == 1 ? 1 : -1);
		}
}

void printArr(int A[N][M])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
			printf("%4d ", A[i][j]);
		printf("\n");
	}
}
void avereg(int matr[N][M], int col)
{
	int sum = 0;
	double avg;
	if (col < M / 2)
		for (int i = 0; i < N / 2; i++)
			sum += matr[i][col];
	else
		if (col < M)
			for (int i = N / 2; i < N; i++)
				sum += matr[i][col];
		else
			printf("Некоректный ввод");
	avg = sum / (double)N * 2;
	printf("Столбец:%d\tСреднее арифметическое:%f\n", col+1, avg);
}

void lab3_2()
{
	int matr[N][M];
	getArr(matr);
	printArr(matr);
	for (int i = 0; i < M; i++)
		avereg(matr, i);
}
int main()
{
	setlocale(0, "russian");
	int answer;
	lab3_2();
	for (;;)
	{
		printf("Продолжить выполнение? (1 - \"ДА\", 2 - \"НЕТ\")\n");
		scanf("%d", &answer);
		if (answer == 1)
			lab3_2();
		else
			if (answer == 2)
				break;
			else
				printf("Некоректнй ввод\n");

	}
	return 0;
}