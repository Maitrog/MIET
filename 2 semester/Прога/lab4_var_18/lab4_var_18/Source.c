#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>

//Array initialize function
int* InitArray(int size)
{
	int* arr = (int*)malloc(size * sizeof(int));	//Allocate memory
	for (int i = 0; i < size; i++)
	{
		*(arr + i) = rand() % 100 * (rand()%2==1?-1:1);	//Generate random number
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

//Search function for last negative element
int* FirstPositiveElement(int* arr, int size)
{
	int* lastNegativeElement = (int *)malloc(sizeof(int));
	for (int i = size - 1; i > 0; i--)
		if (arr[i] < 0)
		{
			lastNegativeElement = arr + i;
			break;
		}

	return lastNegativeElement;
}

//Search function for arithmetic mean after element
double AverageAfterElenent(int* arr, int size, int* element)
{
	int* tp;
	double sum = 0, count = 0;
	for (tp = element, tp++; tp < arr + size; tp++)
	{
		sum = sum + *tp;
		count++;
	}
	if (count == 0)
		return 0;
	return sum/count;
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

//Summarising elements in left and right triangle
int SumTotalInRange(int** matrix, int dim)
{
	int sum = 0;
	//Sum in left triangle
	for (int j = 0; j < dim / 2; j++)
		for (int i = j; i < dim - j; i++)
			sum += matrix[i][j];

	//Sum in right triangle
	for (int j = dim / 2; j < dim; j++)
		for (int i = dim - j - 1; i < j + 1; i++)
			sum += matrix[i][j];

	return sum;
}

//Search function for negative elements quantity in odd columns
int* NagativeElementInOddColumn(int** matrix, int dim)
{
	int* neg = (int*)malloc(dim % 2 == 0 ? (dim / 2) : (dim / 2 + 1) * sizeof(int));	//Allocate memory for negative elements quantity in odd columns
	
	//Set to zero for all quantities
	for (int i = 0; i < (dim % 2 == 0 ? (dim / 2) : (dim / 2 + 1)); i++)
		neg[i] = 0;

	for (int j = 0; j < dim; j+=2)
		for (int i = 0; i < dim; i++)
		{
			if (matrix[i][j] < 0)
				neg[j/2]++;
		}
	return neg;
}

//Summarising elements in left triangle and summarising elements in right triangle 
int* SumInRange(int** matrix, int dim)
{
	int* sum = (int*)malloc(sizeof(int) * 2);
	sum[0] = 0;
	sum[1] = 0;

	//Sum in left triangle
	for (int j = 0; j < dim / 2; j++)
		for (int i = j; i < dim - j; i++)
			sum[0] += matrix[i][j];

	//Sum in right triangle
	for (int j = dim / 2; j < dim; j++)
		for (int i = dim - j - 1; i < j + 1; i++)
			sum[1] += matrix[i][j];

	return sum;
}

int main()
{
	setlocale(0, "russian");
	time_t k;
	srand(time(&k));










	//-----------Level 1 exercise 1-----------
	printf("-----------Level 1 exercise 1-----------");
	int* A, * B;
	int N1, N2;
	int* negA, * negB;
	double avgA, avgB;
	
	printf("\nEnter array A size: ");
	scanf("%d", &N1);
	printf("\nEnter array B size: ");
	scanf("%d", &N2);

	A = InitArray(N1);	//Initialize array A
	B = InitArray(N2);	//Initialize array B

	negA = FirstPositiveElement(A, N1);	//Find the last negative element in array A
	negB = FirstPositiveElement(B, N2);	//Find the last negative element in array B

	printf("Array A: ");
	PrintArr(A, N1);		//Printing the array A
	printf("Array B: ");
	PrintArr(B, N2);		//Printing the array B

	printf("\nLast negative element in array A");
	printf("\nAddress: %p", negA);	//Printing the last negative element address in array A
	printf("\nValue: %d", *negA);	//Printing the last negative element address in array B

	printf("\nLast negative element in array B\n");
	printf("\nAddress: %p", negB);	//Printing last negative element value in array A
	printf("\nValue: %d", *negB);	//Printing last negative element value in array B

	avgA = AverageAfterElenent(A, N1, negA);	//Find for arithmetic mean after last negative element in array A
	avgB = AverageAfterElenent(B, N2, negB);	//Find for arithmetic mean after last negative element in array B

	printf("\nThe average after last negative element in array A: %lf", avgA);
	printf("\nThe average after last negative element in array B: %lf", avgB);
	
	free(A);	//Clear memory
	free(B);










	//----------Level 1 exercise 2-----------
	printf("\n-----------Level 1 exercise 2-----------");
	int N = 10;
	int** Matrix;
	Matrix = InitMatrix(N);	//Initialize matrix Matrix

	printf("\nMatrix:\n");
	PrintMatrix(Matrix, N);	//Printing the matrix Matrix

	int MatrixSum = SumTotalInRange(Matrix, N);	//Find total sum in area (left and right triangle)
	printf("\nSum in area: %d", MatrixSum); 

	//Clear memory
	for (int i = 0; i < N; i++)
		free(Matrix[i]);
	free(Matrix);










	//-----------Level 2 exercise 1-----------
	printf("\n-----------Level 2 exercise 1-----------");
	int** Matrix2;
	int* neg;
	Matrix2 = InitMatrix(N);	//Initialize matrix Matrix2

	printf("\nMatrix:\n");
	PrintMatrix(Matrix2, N);	//Printing the matrix Matrix2
	neg = NagativeElementInOddColumn(Matrix2, N);	//Find the negative elements quantity in odd columns

	printf("\nCount negative element in odd column: ");
	PrintArr(neg, (N % 2 == 0 ? (N / 2) : (N / 2 + 1)));	//Printing the negative elements quantity in odd columns

	//Clear memory
	for (int i = 0; i < N; i++)
		free(Matrix2[i]);
	free(Matrix2);










	//-----------Level 2 exercise 2-----------
	printf("\n-----------Level 2 exercise 2-----------");

	int** Matrix3;
	int* sum;

	Matrix3 = InitMatrix(N);	//Initialize matrix Matrix3

	printf("\nMatrix:\n");
	PrintMatrix(Matrix3, N);	//Printing the matrix Matrix3

	sum = SumInRange(Matrix3, N);	//Find the sum in left triangle and find the sum in right triangle
	printf("\nSum in left triangle: %d", sum[0]);
	printf("\nSum in right triangle: %d", sum[1]);

	//Clear memory
	for (int i = 0; i < N; i++)
		free(Matrix3[i]);
	free(Matrix3);
	free(sum);

	return 0;
}