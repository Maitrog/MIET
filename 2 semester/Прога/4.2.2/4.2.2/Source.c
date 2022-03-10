#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
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
		for (int j = 0; j < n; j++)
			printf("%8d", *(*(ptr + i) + j));
}


int main()
{
	time_t k;
	srand(time(&k));
	int** A;
	A = inp_arr(N);
	print_arr(A, N);
}