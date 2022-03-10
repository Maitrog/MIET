#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>

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

int** InitMatrix(int row, int col)
{
	int** ptr = (int**)malloc(row * sizeof(int*));
	for (int i = 0; i < row; i++)
	{
		*(ptr + i) = (int*)malloc(col * sizeof(int));
		for (int j = 0; j < col; j++)
			*(*(ptr + i) + j) = rand() % 100 * (rand() % 2 == 1 ? -1 : 1);
	}
	return ptr;
}

void PrintMatrix(int** matrix, int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			printf("%8d", *(*(matrix + i) + j));
		printf("\n");
	}
	printf("\n");
}


int* LastNegativeElement(int* p, int begin, int end)
{
	int* min_ptr = begin - 1;
	for (int i = begin; i < end; i++)
		if (*(p + i) < 0)
			min_ptr = (p + i);

	return min_ptr;
}

int* Max(int* begin, int* end)
{
	if (begin > end)
		return end;
	int* max_ptr = begin;
	for (int* i = begin; i <= end; i++)
		if (*i > *max_ptr)
			max_ptr = i;

	return max_ptr;
}


int CountPositiveElement(int** matr, int row, int col)
{
	int count = 0;
	for (int i = row / 2; i < row; i++)
		for (int j = 0; j < col; j++)
			if (matr[i][j] > 0)
				count++;

	return count;
}

int* CountNegativeElement(int** matrix, int row, int col)
{
	int* countNegative = (int*)malloc(row / 2 * sizeof(int));

	for (int i = 0; i < col / 2; i++)
		countNegative[i] = 0;

	for (int j = 1; j < col; j += 2)
		for (int i = 0; i < row; i++)
			if (matrix[i][j] < 0)
				countNegative[j / 2]++;

	return countNegative;
}

int* CountPositiveAndNegativeElement(int** matr, int row, int col)
{
	int* count = (int*)malloc(2*sizeof(int));
	count[0] = 0;
	count[1] = 0;

	for (int i = row / 2; i < row; i++)
		for (int j = 0; j < col; j++)
			if (matr[i][j] > 0)
				count[0]++;

	for (int i = row / 2; i < row; i++)
		for (int j = 0; j < col; j++)
			if (matr[i][j] < 0)
				count[1]++;

	return count;
}

int main()
{
	setlocale(0, "russian");
	time_t k;
	srand(time(&k));
	int run = 1, c;

	while (run)
	{
		printf("\n1.������� 1 ������� 1");
		printf("\n2.������� 1 ������� 2");
		printf("\n3.������� 2 ������� 1");
		printf("\n4.������� 2 ������� 2");
		printf("\n5.�����");
		printf("\n������� ����� �������: ");
		scanf("%d", &c);

		if (c == 1)
		{
			int* A, * B;
			int N1, N2;
			int* negA, *negB;

			printf("\n������� ������ ������� �: ");
			scanf("%d", &N1);
			printf("\n������� ������ ������� B: ");
			scanf("%d", &N2);

			A = InitArray(N1);
			B = InitArray(N2);

			negA = LastNegativeElement(A, 0, N1);
			negB = LastNegativeElement(B, 0, N2);

			printf("\n������ A: ");
			PrintArr(A, N1);
			printf("\n������ B: ");
			PrintArr(B, N2);


			printf("\n������������ ������� �� ������ ����� ������� �: %d", *Max(negA + 1, A + N1 - 1));

			printf("\n������������ ������� �� ������ ����� ������� B: %d", *Max(negB + 1, B + N2 - 1));

			free(A);
			free(B);
		}
		else if (c == 2)
		{
			int** matrix;
			matrix = InitMatrix(10, 12);

			PrintMatrix(matrix, 10, 12);

			printf("���������� ������������� ��������� � �������������� �������: %d", CountPositiveElement(matrix, 10, 12));
		}
		else if (c == 3)
		{
			int N, M;
			int** matrix;
			int* countNegative;
			printf("������� ���������� �����: ");
			scanf("%d", &N);
			printf("������� ���������� ��������: ");
			scanf("%d", &M);

			matrix = InitMatrix(N, M);

			PrintMatrix(matrix, N, M);

			countNegative = CountNegativeElement(matrix, N, M);

			printf("���������� ������������� ��������� � ������ ��������(��������� � 1):\n");
			PrintArr(countNegative, M / 2);

		}
		else if (c == 4)
		{
			int N, M;
			int** matrix;
			int* count;
			printf("������� ���������� �����: ");
			scanf("%d", &N);
			printf("������� ���������� ��������: ");
			scanf("%d", &M);

			matrix = InitMatrix(N, M);

			PrintMatrix(matrix, N, M);

			count = CountPositiveAndNegativeElement(matrix, N, M);

			printf("\n���������� ������������� ��������� � �������������� �������: %d", count[0]);
			printf("\n���������� ������������� ��������� � �������������� �������: %d", count[1]);

		}
		else if (c == 5)
		{
			run = 0;
		}
	}
}