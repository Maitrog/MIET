#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 5
#define M 5
int inp_arr(int n,int m)
{
	int** ptr = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++)
	{
		*(ptr + i) = (int*)malloc(m * sizeof(int));
		for (int j = 0; j < m; j++)
			*(*(ptr + i) + j) = rand() % 100;
	}
	return ptr;
}
void print_arr(int** ptr, int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			printf("%8d", *(*(ptr + i) + j));
		printf("\n");
	}
}

int nullfound(int** ptr, int n, int m)
{
	int nullcount = 0;
	for (int i = 0; i < n / 2; i++)
	{
		for (int j = i; j < m - i; j++)
			if (*(*(ptr+i)+j) == 0)
				nullcount++;
	}
	for (int i = n/2; i < n; i++)
	{
		for (int j = m - i - 1; j < i + 1; j++)
			if (*(*(ptr + i)+j) == 0)
				nullcount++;
	}
	return nullcount;
}
int main()
{
	time_t k;
	srand(time(&k));
	int** table;
	int nulls;
	table = inp_arr(N, M);
	print_arr(table, N, M);
	nulls = nullfound(table, N, M);
	printf("%d\n", nulls);
	for (int i = 0; i < N; i++)
		free(table[i]);
	free(table);

}