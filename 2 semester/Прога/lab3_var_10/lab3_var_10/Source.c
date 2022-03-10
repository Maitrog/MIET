#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <math.h>

int* InitArray(int size)
{
	int* arr = (int*)malloc(size * sizeof(int));
	for (int i = 0; i < size; i++)
	{
		*(arr + i) = rand() % 100 * (rand() % 2 == 1 ? -1 : 1);
	}
	return arr;
}

void PrintArr(int* arr, int size)
{
	for (int i = 0; i < size; i++)
		printf("%d\t", *(arr + i));
	printf("\n");
}

int LastPositiveElement(int* arr, int size)
{
	int index = -1;
	for (int i = 0; i < size; i++)
		if (arr[i] > 0)
			index = i;

	return index;
}

int Min(int* arr, int begin, int end)
{
	int min = arr[0];
	for (int i = begin; i < end; i++)
		if (arr[i] < min)
			min = arr[i];

	return min;
}

int** InitMatrix(int dim)
{
	int** ptr = (int**)malloc(dim * sizeof(int*));
	for (int i = 0; i < dim; i++)
	{
		*(ptr + i) = (int*)malloc(dim * sizeof(int));
		for (int j = 0; j < dim; j++)
			*(*(ptr + i) + j) = rand() % 100 * (rand() % 2 == 1 ? -1 : 1);
	}
	return ptr;
}

void PrintMatrix(int** matrix, int dim)
{
	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
			printf("%8d", *(*(matrix + i) + j));
		printf("\n");
	}
	printf("\n");
}

int MaxLeftUpTriangle(int** matrix, int dim, int row)
{
	int max = 0;
	for (int j = row; j < dim; j++)
		if (abs(matrix[row][j]) > max)
			max = abs(matrix[row][j]);

	return max;
}

int main()
{
	setlocale(0, "russian");
	time_t k;
	srand(time(&k));
	int run = 1, c;

	while (run)
	{
		printf("\n1.Задание 1");
		printf("\n2.Задание 2");
		printf("\n3.Выход");
		printf("\nВведите номер задания: ");
		scanf("%d", &c);

		if (c == 1)
		{
			int* A, * B;
			int N1, N2;
			int posA, posB;

			printf("\nВведите размер массива А: ");
			scanf("%d", &N1);
			printf("\nВведите размер массива B: ");
			scanf("%d", &N2);

			A = InitArray(N1);
			B = InitArray(N2);

			posA = LastPositiveElement(A, N1);
			posB = LastPositiveElement(B, N2);

			printf("\nМассив A: ");
			PrintArr(A, N1);
			printf("\nМассив B: ");
			PrintArr(B, N2);

			printf("\nИндекс последнего положительного элемента в массиве A: %d", posA);

			printf("\nМинимальный элемент в первой части массива А: %d", Min(A, 0, posA));

			printf("\nИндекс последнего положительного элемента в массиве B: %d", posB);

			printf("\nМинимальный элемент в первой части массива B: %d", Min(B, 0, posB));

			free(A);
			free(B);
		}
		else if (c == 2)
		{
			int** matrix;
			int N;
			printf("\nВведите размерность матрицы: ");
			scanf("%d", &N);
			matrix = InitMatrix(N);

			PrintMatrix(matrix, N);

			for (int i = 0; i < N; i++)
				printf("\nМаксимум в %d строке: %d", i, MaxLeftUpTriangle(matrix, N, i));

			for (int i = 0; i < N; i++)
				free(matrix[i]);

			free(matrix);
		}
		else if (c == 3)
		{
			run = 0;
		}
	}
	return 0;
}