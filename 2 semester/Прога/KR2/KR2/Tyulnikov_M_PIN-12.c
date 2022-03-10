//¬¿–»¿Õ“ 1
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10
#define M 10

//double** inp_arr(int n, int m)
//{
//	double** arr = (double**)malloc(n * sizeof(double*));
//	for (int i = 0; i < n; i++)
//	{
//		*(arr + i) = (double*)malloc(m * sizeof(double));
//		for (int j = 0; j < m; j++)
//			*(*(arr + i) + j) = rand() % 100 + (double)rand() / RAND_MAX;
//	}
//	return arr;
//}
//
void print_arr(double** arr, int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			printf("%-10lf ", *(*(arr + i) + j));
		printf("\n");
	}
}
//
//double max_found(double** arr, int n, int m, int *ptr_min)
//{
//	double max = **arr;
//	for (size_t i = 0; i < n; i++)
//	{
//		for (size_t j = 0; j < m; j++)
//			if (*(*(arr + i) + j) > max)
//			{
//				max = *(*(arr + i) + j);
//				(*ptr_min) = (*(arr + i) + j);
//			}
//	}
//	return max;
//}

void main()
{
	time_t k;
	srand(time(&k));
	int** mas_max;
	int** arr = (int**)malloc(M * sizeof(int*) + N * M * sizeof(int));
	int* start = ((char*)arr + M * sizeof(int*));
	for (int i = 0; i < M; i++)
	{
		arr[i] = start + i * N;
	}
	for(int i = 0; i < M; i++)
		for(int j=0;j<N;j++)
		{
			arr[i][j] = rand() % 100 - 50;
		}
	print_arr(arr, N, M);
	/*int ptr_max = 0;
	A = inp_arr(N, M);
	print_arr(A, N, M);
	mas_max = max_found(A, N, M, &ptr_max);
	printf("Max item: %f\nItem position: %p", mas_max, ptr_max);
	for (int i = 0; i < N; i++)
		free(A[i]);*/
	//free(A);
}