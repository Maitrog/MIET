#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <math.h>
#define N 10

int** inp_arr(int n)
{
	int** ptr = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++)
	{
		*(ptr + i) = (int*)malloc(n * sizeof(int));
		for (int j = 0; j < n; j++)
			*(*(ptr + i) + j) = rand() % 100;
	}
	return ptr;
}

void print_arr(int** ptr, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			printf("%8d", *(*(ptr + i) + j));
		printf("\n");
	}
	printf("\n");
}

void print_mas(int* ptr, int n)
{
	for (int i = 0; i < n; i++)
		printf("%8d", *(ptr + i));
	printf("\n");
}

int* min_found(int** ptr, int n)
{
	int* ptr_mas = (int*)malloc(n * sizeof(int));
	for (int j = 0; j < n; j++)
	{
		*(ptr_mas + j) = *(*ptr + j);
		for (int i = 0; i < n; i++)
			if (*(ptr_mas + j) > abs(*(*(ptr + i) + j)))
				*(ptr_mas + j) = abs(*(*(ptr + i) + j));
	}
	return ptr_mas;
}
int main()
{
	time_t k;
	srand(time(&k));
	int** A, *min_mas;
	A = inp_arr(N);
	print_arr(A, N);
	min_mas = min_found(A, N);
	print_mas(min_mas, N);
	for (int i = 0; i < N; i++)
		free(A[i]);
	free(A);
	free(min_mas);
}