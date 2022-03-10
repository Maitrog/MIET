#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>

#define N1 10
#define N2 20

void getArr(int A[], int N)
{
	time_t k;
	srand(time(&k)+rand());
	int minus = 1;
	for (int i = 0; i < N; i++)
	{
		//minus = rand();
		A[i] = rand() % 10 * (minus % 2 == 1 ? 1 : -1);
	}
}

void printArr(int A[],int N)
{
	for (int i = 0; i < N; i++)
		printf("%d ", A[i]);
}

int nullfound(int A[], int N)
{
	int null = N;
	for(int i=0; i< N; i++)
		if (A[i] == 0)
		{
			null = i;
			break;
		}
	return null;
}

void lab3()
{
	int A[N1], B[N2], nullA, nullB;
	int sumABeforeNull = 0, sumAAfterNull = 0, sumBBeforeNull = 0, sumBAfterNull = 0;
	getArr(A, N1);
	nullA = nullfound(A, N1);
	for (int i = 0; i < nullA; i++)
		sumABeforeNull += A[i];
	for (int i = nullA; i < N1; i++)
		sumAAfterNull += A[i];
	printf("Массив A\n");
	printArr(A, N1);
	printf("\nСумма до нуля:%d\nСумма после нуля:%d\n", sumABeforeNull, sumAAfterNull);

	getArr(B, N2);
	nullB = nullfound(B, N2);
	for (int i = 0; i < nullB; i++)
		sumBBeforeNull += B[i];
	for (int i = nullB; i < N2; i++)
		sumBAfterNull += B[i];
	printf("\nМассив B\n");
	printArr(B, N2);
	printf("\nСумма до нуля:%d\nСумма после нуля:%d\n", sumBBeforeNull, sumBAfterNull);
}

int main()
{
	setlocale(0, "russian");
	int answer;
	lab3();
	for (;;)
	{
		printf("Продолжить выполнение? (1 - \"ДА\", 2 - \"НЕТ\")\n");
		scanf("%d", &answer);
		if (answer == 1)
			lab3();
		else
			if (answer == 2)
				break;
			else
				printf("Некоректнй ввод\n");

	}
}