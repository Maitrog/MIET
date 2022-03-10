#include <iostream>
#include <ctime>

double* initArr(int n)
{

	double* p = new double[n];
	for (int i = 0; i < n; i++)
	{
		*(p + i) = double(rand() % 100) + double(rand())/RAND_MAX;
	}
	return p;
}

void printArr(double* p, int n)
{
	for (int i = 0; i < n; i++)
		std::cout << *(p + i) << " ";
	std::cout << std::endl;
}

void printArr(int* p, int n)
{
	for (int i = 0; i < n; i++)
		std::cout << *(p + i) << " ";
	std::cout << std::endl;
}

double* Max(double* p, int begin, int end)
{
	double* max_ptr = p;
	for (int i = begin; i < end; i++)
	{
		if (*(p + i) > *max_ptr)
		{
			max_ptr = (p + i);
		}
	}
	return max_ptr;
}

int sumAfterMax(double* p, int size, double* max)
{
	double* tp;
	double sum = 0;
	for (tp = max, tp++; tp < p + size; tp++)
		sum = sum + *tp;
	return sum;
}

int** initMatrix(int n, int m)
{
	int** ptr = new int*[n];
	for (int i = 0; i < n; i++)
	{
		*(ptr + i) = new int[n];
		for (int j = 0; j < m; j++)
			*(*(ptr + i) + j) = rand() % 100 * (rand() % 2 ? -1 : 1);
	}
	return ptr;
}

void printMatrix(int** ptr, int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			std::cout.width(8);
			std::cout << *(*(ptr + i) + j);
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

int nullFind(int** ptr, int n, int m)
{
	int nullcount = 0;
	for (int i = 0; i < n / 2; i++)
	{
		for (int j = i; j < m - i; j++)
			if (*(*(ptr + i) + j) == 0)
				nullcount++;
	}
	for (int i = n / 2; i < n; i++)
	{
		for (int j = m - i - 1; j < i + 1; j++)
			if (*(*(ptr + i) + j) == 0)
				nullcount++;
	}
	return nullcount;
}

int* MinColumns(int** ptr, int n, int m)
{
	int* ptr_mas = new int[m];
	for (int j = 0; j < n; j++)
	{
		*(ptr_mas + j) = abs(*(*ptr + j));
		for (int i = 0; i < m; i++)
			if (*(ptr_mas + j) > abs(*(*(ptr + i) + j)))
				*(ptr_mas + j) = abs(*(*(ptr + i) + j));
	}
	return ptr_mas;
}

int* NullAndPositiveFind(int** ptr, int n, int m)
{
	int nullCount = 0;
	int positiveCount = 0;
	for (int i = 0; i < n / 2; i++)
	{
		for (int j = i; j < m - i; j++)
			if (*(*(ptr + i) + j) == 0)
				nullCount++;
	}
	for (int i = n / 2; i < n; i++)
	{
		for (int j = m - i - 1; j < i + 1; j++)
			if (*(*(ptr + i) + j) > 0)
				positiveCount++;
	}

	int* mas = new int[2];
	mas[0] = nullCount;
	mas[1] = positiveCount;
	return mas;
}

int main()
{
	const int N = 10;
	const int M = 10;
	setlocale(0, "russian");
	time_t k;
	srand(time(&k));

	std::cout << "-------Уровень 1 Задание 1------" << std::endl;
	double* A, * B;
	double *maxA, *maxB, sumA, sumB;
	A = initArr(N);
	printArr(A, N);
	maxA = Max(A, 0, N);
	sumA = sumAfterMax(A, N, maxA);
	B = initArr(M);
	printArr(B, M);
	maxB = Max(B, 0, M);
	sumB = sumAfterMax(B, M, maxB);
	std::cout << "Max A: " << *maxA << " Sum A: " << sumA << std::endl;
	std::cout << "Max B: " << *maxB << " Sum B: " << sumB << std::endl;
	if (sumA < sumB)
		std::cout << "Сумма чисел после максимального элемента в первом массиве меньше" << std::endl;
	else
		if (sumB < sumA)
			std::cout << "Сумма чисел после максимального элемента во втором массиве меньше" << std::endl;
		else
			std::cout << "Суммы элементов равны" << std::endl;
	delete[] A;
	delete[] B;



	std::cout << "-------Уровень 1 Задание 2------" << std::endl;
	int** tab;
	int nulls;
	tab = initMatrix(N, N);
	printMatrix(tab, N, N);
	nulls = nullFind(tab, N, N);
	std::cout << "Нулей в заштрихованной области матрицы: " << nulls << std::endl;
	for (int i = 0; i < N; i++)
		delete[] tab[i];
	delete[] tab;



	std::cout << "-------Уровень 2 Задание 1------" << std::endl;
	int** tab2, * min_mas;
	tab2 = initMatrix(N, N);
	printMatrix(tab2, N, N);
	min_mas = MinColumns(tab2, N, N);
	printArr(min_mas, N);
	for (int i = 0; i < N; i++)
		delete[] tab2[i];
	delete[] tab2;
	delete[] min_mas;


	std::cout << "-------Уровень 2 Задание 2------" << std::endl;
	int** tab3, * nullAndPos;
	tab3 = initMatrix(N, N);
	printMatrix(tab3, N, N);
	nullAndPos = NullAndPositiveFind(tab3, N, N);
	std::cout << "Количество нулей: " << nullAndPos[0] << " Количество положительных элементов: " << nullAndPos[1];
	for (int i = 0; i < N; i++)
		delete[] tab3[i];
	delete[] tab3;
	delete[] nullAndPos;
	return 0;
}