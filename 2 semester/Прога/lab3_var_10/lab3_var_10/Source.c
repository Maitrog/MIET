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
		printf("\n1.������� 1");
		printf("\n2.������� 2");
		printf("\n3.�����");
		printf("\n������� ����� �������: ");
		scanf("%d", &c);

		if (c == 1)
		{
			int* A, * B;
			int N1, N2;
			int posA, posB;

			printf("\n������� ������ ������� �: ");
			scanf("%d", &N1);
			printf("\n������� ������ ������� B: ");
			scanf("%d", &N2);

			A = InitArray(N1);
			B = InitArray(N2);

			posA = LastPositiveElement(A, N1);
			posB = LastPositiveElement(B, N2);

			printf("\n������ A: ");
			PrintArr(A, N1);
			printf("\n������ B: ");
			PrintArr(B, N2);

			printf("\n������ ���������� �������������� �������� � ������� A: %d", posA);

			printf("\n����������� ������� � ������ ����� ������� �: %d", Min(A, 0, posA));

			printf("\n������ ���������� �������������� �������� � ������� B: %d", posB);

			printf("\n����������� ������� � ������ ����� ������� B: %d", Min(B, 0, posB));

			free(A);
			free(B);
		}
		else if (c == 2)
		{
			int** matrix;
			int N;
			printf("\n������� ����������� �������: ");
			scanf("%d", &N);
			matrix = InitMatrix(N);

			PrintMatrix(matrix, N);

			for (int i = 0; i < N; i++)
				printf("\n�������� � %d ������: %d", i, MaxLeftUpTriangle(matrix, N, i));

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