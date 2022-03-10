#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 4

double** create_arr(int n)
{
	double** arr = (double**)malloc(sizeof(double)*n);
	for (int i = 0; i < n; i++)
	{
		*(arr + i) = (double*)malloc(sizeof(double)*n);
		for (int j = 0; j < n; j++)
			*(*(arr + i) + j) = rand() % 10 + (double)rand() / RAND_MAX;
	}
	return arr;
}

void print_arr(double** arr, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			printf("%lf\t", *(*(arr + i) + j));
		printf("\n");
	}
}

double sum(double** arr, int n)
{
	double sum = 0;
	for (int i = 0; i < n / 2; i++)
		for (int j = i; j < n - i; j++)
			sum = sum + *(*(arr + i) + j);
	for (int i = n/2; i < n; i++)
		for (int j = n - i - 1; j < i+1; j++)
			sum = sum + *(*(arr + i) + j);
	return sum;
}

int main()
{
	double s;
	srand(time(NULL));
	double** arr;
	arr = create_arr(N);
	print_arr(arr, N);
	s = sum(arr, N);
	printf("%lf", s);
}