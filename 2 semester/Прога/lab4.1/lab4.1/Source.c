#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10
#define M 10

int inp_arr(int n)	
{
	
	int* p = malloc(N * sizeof(int));
	for (int i = 0; i < n; i++)
	{
		*(p + i) = rand() % 100;
	}
	return p;
}

void printArr(int* p, int n)
{
	for (int i = 0; i < n; i++)
		printf("%d\t", *(p + i));
	printf("\n");
}

int maxfound(int* p, int n)
{
	int max_index = p;
	int* max;
	max = max_index;
	for (int i = 0; i < n; i++)
	{
		if (*(p + i) > * max)
		{
			max_index = (p + i);
			max = max_index;
		}
	}
	return max_index;
}
int sumAfterMax(int* p, int n, int max)
{
	int* tp;
	int sum = 0;
	for (tp = max, tp++ ; tp < p + n; tp++)
		sum = sum + *tp;
	return sum;
}
int main()
{
	setlocale (0, "russian");
	time_t k;
	srand(time(&k));
	int* A, * B;
	int maxA, maxB, sumA, sumB;
	A = inp_arr(N);
	printArr(A, N);
	maxA = maxfound(A, N);
	sumA = sumAfterMax(A, N, maxA);
	B = inp_arr(M);
	printArr(B, M);
	maxB = maxfound(B, M);
	sumB = sumAfterMax(B, M, maxB);
	if (sumA < sumB)
		printf("Сумма чисел после максимального элемента в первом массиве меньше\n");
	else
		if (sumB < sumA)
			printf("Сумма чисел после максимального элемента во втором массиве меньше\n");
		else
			printf("Суммы элементов равны");
	free(A);
	free(B);
}