#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Source.h"
using namespace std;

void main()
{
	srand(time(NULL));
	int rowLeftMatrix, colLeftMatrix, rowRightMatrix, colRightMatrix, k, normalizedMatrixSize = 2;
	system("chcp 1251");
	cout << "Вас приветствует программа" << endl <<
		"быстрого умножения методом Штрассена\n\n";

	InitializeMatrixSize(rowLeftMatrix, colLeftMatrix, "Введите размеры первой матрицы\n");
	InitializeMatrixSize(rowRightMatrix, colRightMatrix, "Введите размеры второй матрицы\n");

	int** leftMatrix, ** rightMatrix;
	CreateMatrix(leftMatrix, rowLeftMatrix, colLeftMatrix);
	CreateMatrix(rightMatrix, rowRightMatrix, colRightMatrix);

	do
	{
		cout << "Выберите способ заполнения матриц\n" <<
			"1 - Вручную \n2 - Случайным образом\n";
		cin >> k;
	} while (k < 1 || k > 2);
	switch (k)
	{
	case 1:
		InitializeMatrix(leftMatrix, rowLeftMatrix, colLeftMatrix);
		InitializeMatrix(rightMatrix, rowRightMatrix, colRightMatrix);
		break;
	case 2:
		AutoInitializeMatrix(leftMatrix, rowLeftMatrix, colLeftMatrix);
		AutoInitializeMatrix(rightMatrix, rowRightMatrix, colRightMatrix);
		break;
	}
	cout << "\nМатрица 1\n\n";
	PrintMatrix(leftMatrix, rowLeftMatrix, colLeftMatrix);
	cout << "\nМатрица 2\n\n";
	PrintMatrix(rightMatrix, rowRightMatrix, colRightMatrix);

	normalizedMatrixSize = GetNormalizedMatrixSize(rowLeftMatrix, rowRightMatrix, colLeftMatrix, colRightMatrix);
	ResizeMatrix(leftMatrix, rowLeftMatrix, colLeftMatrix, normalizedMatrixSize, normalizedMatrixSize);
	ResizeMatrix(rightMatrix, rowRightMatrix, colRightMatrix, normalizedMatrixSize, normalizedMatrixSize);

	cout << "Приведенные матрицы\n";
	cout << "\nМатрица 1\n\n";
	PrintMatrix(leftMatrix, normalizedMatrixSize, normalizedMatrixSize);
	cout << "\nМатрица 2\n\n";
	PrintMatrix(rightMatrix, normalizedMatrixSize, normalizedMatrixSize);

	int** d, ** d1, ** d2, ** h1, ** h2, ** v1, ** v2;
	CreateZeroMatrix(d, normalizedMatrixSize / 2, normalizedMatrixSize / 2);
	CreateZeroMatrix(d1, normalizedMatrixSize / 2, normalizedMatrixSize / 2);
	CreateZeroMatrix(d2, normalizedMatrixSize / 2, normalizedMatrixSize / 2);
	CreateZeroMatrix(h1, normalizedMatrixSize / 2, normalizedMatrixSize / 2);
	CreateZeroMatrix(h2, normalizedMatrixSize / 2, normalizedMatrixSize / 2);
	CreateZeroMatrix(v1, normalizedMatrixSize / 2, normalizedMatrixSize / 2);
	CreateZeroMatrix(v2, normalizedMatrixSize / 2, normalizedMatrixSize / 2);

	for (int i = 0; i < normalizedMatrixSize / 2; i++)
	{
		for (int j = 0; j < normalizedMatrixSize / 2; j++)
		{
			for (int z = 0; z < normalizedMatrixSize / 2; z++)
			{
				int leftMatrixFirstQuarter = leftMatrix[i][z + normalizedMatrixSize / 2];
				int leftMatrixSecondQuarter = leftMatrix[i][z];
				int leftMatrixThirdQuarter = leftMatrix[i + normalizedMatrixSize / 2][z];
				int leftMatrixFourthQuarter = leftMatrix[i + normalizedMatrixSize / 2][z + normalizedMatrixSize / 2];
				int rightMatrixFirstQuarter = rightMatrix[z][j + normalizedMatrixSize / 2];
				int rightMatrixSecondQuarter = rightMatrix[z][j];
				int rightMatrixThirdQuarter = rightMatrix[z + normalizedMatrixSize / 2][j];
				int rightMatrixFourthQuarter = rightMatrix[z + normalizedMatrixSize / 2][j + normalizedMatrixSize / 2];

				d[i][j] += (leftMatrixSecondQuarter + leftMatrixFourthQuarter) * (rightMatrixSecondQuarter + rightMatrixFourthQuarter);
				d1[i][j] += (leftMatrixFirstQuarter - leftMatrixFourthQuarter) * (rightMatrixThirdQuarter + rightMatrixFourthQuarter);
				d2[i][j] += (leftMatrixThirdQuarter - leftMatrixSecondQuarter) * (rightMatrixSecondQuarter + rightMatrixFirstQuarter);
				h2[i][j] += (leftMatrixThirdQuarter + leftMatrixFourthQuarter) * rightMatrixSecondQuarter;
				h1[i][j] += (leftMatrixSecondQuarter + leftMatrixFirstQuarter) * rightMatrixFourthQuarter;
				v1[i][j] += leftMatrixSecondQuarter * (rightMatrixFirstQuarter - rightMatrixFourthQuarter);
				v2[i][j] += leftMatrixFourthQuarter * (rightMatrixThirdQuarter - rightMatrixSecondQuarter);
			}
		}
	}

	int** resultMatrix;
	CreateMatrix(resultMatrix, normalizedMatrixSize, normalizedMatrixSize);

	for (int i = 0; i < normalizedMatrixSize / 2; i++)
	{
		for (int j = 0; j < normalizedMatrixSize / 2; j++)
		{
			resultMatrix[i][j] = d[i][j] + v2[i][j] - h1[i][j] + d1[i][j];
			resultMatrix[i][j + normalizedMatrixSize / 2] = v1[i][j] + h1[i][j];
			resultMatrix[i + normalizedMatrixSize / 2][j] = h2[i][j] + v2[i][j];
			resultMatrix[i + normalizedMatrixSize / 2][j + normalizedMatrixSize / 2] = d[i][j] - h2[i][j] + v1[i][j] + d2[i][j];
		}
	}

	cout << "\nРезультирующая матрица\n\n";
	PrintMatrix(resultMatrix, rowLeftMatrix, colRightMatrix);

	DeleteMatrix(leftMatrix, rowLeftMatrix);
	DeleteMatrix(rightMatrix, rowRightMatrix);
	DeleteMatrix(resultMatrix, normalizedMatrixSize);

	DeleteMatrix(d, normalizedMatrixSize / 2);
	DeleteMatrix(d1, normalizedMatrixSize / 2);
	DeleteMatrix(d2, normalizedMatrixSize / 2);
	DeleteMatrix(h1, normalizedMatrixSize / 2);
	DeleteMatrix(h2, normalizedMatrixSize / 2);
	DeleteMatrix(v1, normalizedMatrixSize / 2);
	DeleteMatrix(v2, normalizedMatrixSize / 2);

	system("pause");
}

void InitializeMatrixSize(int& rowLeftMatrix, int& colLeftMatrix, const char* str = "Введите размеры матрицы\n")
{
	do
	{
		cout << str;
		cout << "Введите количество строк: ";
		cin >> rowLeftMatrix;
		cout << "Введите количество столбцов: ";
		cin >> colLeftMatrix;
	} while (rowLeftMatrix <= 0 || colLeftMatrix <= 0);
}

int GetNormalizedMatrixSize(const int& rowLeftMatrix, const int& rowRightMatrix, const int& colLeftMatrix, const int& colRightMatrix)
{
	int max = std::max(std::max(rowLeftMatrix, rowRightMatrix), std::max(colLeftMatrix, colRightMatrix));
	return max & 0b1 ? (max + 1) : max;
}

void DeleteMatrix(int** matrix, const int& row)
{
	for (int i = 0; i < row; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}

void CopyMatrix(int** from, int** to, const int& row, const int& col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			to[i][j] = from[i][j];
		}
	}
}

void CreateZeroMatrix(int**& matrix, const int& row, const int& col)
{
	matrix = new int* [row];
	for (int i = 0; i < row; i++)
	{
		matrix[i] = new int[col];
		memset(matrix[i], 0, col * sizeof(int));
	}
}

void AutoInitializeMatrix(int** matrix, const int& row, const int& col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			matrix[i][j] = rand() % 10;
		}
	}
}

void PrintMatrix(int** matrix, const int& row, const int& col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

void InitializeMatrix(int** matrix, const int& row, const int& col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cin >> matrix[i][j];
		}
	}
}

void CreateMatrix(int**& matrix, const int& row, const int& col)
{
	matrix = new int* [row];
	for (int i = 0; i < row; i++)
	{
		matrix[i] = new int[col];
	}
}

void ResizeMatrix(int**& matrix, const int& oldRow, const int& oldCol, const int& newRow, const int& newCol) {
	if (oldRow != newRow && oldCol != newCol)
	{
		int** newMatrix;
		CreateZeroMatrix(newMatrix, newRow, newCol);
		CopyMatrix(matrix, newMatrix, oldRow, oldCol);
		int** tmp = matrix;
		matrix = newMatrix;
		DeleteMatrix(tmp, oldRow);
	}
}