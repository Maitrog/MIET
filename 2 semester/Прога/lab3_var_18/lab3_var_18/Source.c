#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>

//Array initialize function
int* InitArray(int size)
{
	int* arr = (int*)malloc(size * sizeof(int));	//Allocate memory
	for (int i = 0; i < size; i++)
	{
		*(arr + i) = rand() % 100 * (rand() % 2 == 1 ? -1 : 1);	//Generate random number
	}
	return arr;
}

//Array print function
void PrintArr(int* arr, int size)
{
	for (int i = 0; i < size; i++)
		printf("%d\t", *(arr + i));
	printf("\n");
}

//Search function for first positive element
int* FirstPositiveElement(int* arr, int size)
{
	int firstPositiveElement = -1;
	for (int i = 0; i < size; i++)
		if (arr[i] > 0)
		{
			firstPositiveElement = i;
			break;
		}

	return firstPositiveElement;
}

//Matrix initialize function
int** InitMatrix(int dim)
{
	int** ptr = (int**)malloc(dim * sizeof(int*));	//Allocate memory for rows
	for (int i = 0; i < dim; i++)
	{
		*(ptr + i) = (int*)malloc(dim * sizeof(int));	//Allocate memory for columns
		for (int j = 0; j < dim; j++)
			*(*(ptr + i) + j) = rand() % 100 * (rand() % 2 == 1 ? -1 : 1);	//Generate random number
	}
	return ptr;
}

//Matrix print function
void PrintMatrix(int** ptr, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			printf("%8d", *(*(ptr + i) + j));
		printf("\n");
	}
	printf("\n");
}

int PositiveElementInRow(int** matrix, int dim, int row)
{
	int count = 0;
	for (int i = dim - row - 1; i < dim; i++)
		if (matrix[row][i] > 0)
			count++;

	return count;
}

int main()
{
	setlocale(0, "russian");
	time_t k;
	srand(time(&k));





	//-----------Exercise 1-----------
	printf("-----------Exercise 1-----------");
	int* A, * B;
	int N1, N2;
	int posA, posB;

	printf("\nEnter array A size: ");
	scanf("%d", &N1);
	printf("\nEnter array B size: ");
	scanf("%d", &N2);

	A = InitArray(N1);	//Initialize array A
	B = InitArray(N2);	//Initialize array B

	posA = FirstPositiveElement(A, N1);	//Find the first positive element in array A
	posB = FirstPositiveElement(B, N2);	//Find the first positive element in array B

	printf("\nArray A: ");
	PrintArr(A, N1);		//Printing the array A
	printf("\nArray B: ");
	PrintArr(B, N2);		//Printing the array B

	printf("\nFirst positive element's index in array A: %d", posA);

	printf("\nPositive elements quantity in first part array A: %d", posA==-1?0:posA);
	printf("\nPositive elements quantity in second part array A: %d", N1 - posA - 1);

	printf("\nFirst positive element's index in array B: %d", posB);

	printf("\nPositive elements quantity in first part array B: %d", posB==-1?0:posB);
	printf("\nPositive elements quantity in second part array B: %d", N2 - posB - 1);

	//Clear memory
	free(A);
	free(B);









	//-----------Exercise 2-----------
	printf("\n-----------Exercise 2-----------");
	int N, row, positiveElementInRow;
	int** Matrix;
	printf("\nEnter matrix dimention: ");
	scanf("%d", &N);
	Matrix = InitMatrix(N);	//Initialize matrix Matrix

	printf("\nMatrix:\n");
	PrintMatrix(Matrix, N);	//Printing the matrix Matrix

	printf("\nEnter row number(0-%d): ", N-1);
	scanf("%d", &row);

	positiveElementInRow = PositiveElementInRow(Matrix, N, row);

	printf("\nRow %d have %d positive elements", row, positiveElementInRow);

	//Clear memory
	for (int i = 0; i < N; i++)
		free(Matrix[i]);
	free(Matrix);

	return 0;
}