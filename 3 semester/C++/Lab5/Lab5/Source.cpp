// Тюльников Михаил ПИН-22 Вариант 24
#include <iostream>
#include <random>
#include <type_traits>
#include <Windows.h>

template <class T>
T* initialisation(int size)
{
	T* array = new T[size];
	for (int i = 0; i < size; i++)
	{
		if (std::is_same<T, int>::value)
			array[i] = rand();
		if (std::is_same<T, double>::value)
			array[i] = rand() + double(rand()) / RAND_MAX;
	}
	return array;
}

template<class T>
int min_index(T* array, int size)
{
	int min = 0;
	for (int i = 1; i < size; i++)
		if (array[i] < array[min])
			min = i;
	return min;
}

template<class T>
int max_index(T* array, int size)
{
	int max = 0;
	for (int i = 1; i < size; i++)
		if (array[i] > array[max])
			max = i;
	return max;
}

template<class T>
T sum(T* array, int size)
{
	int min = min_index(array, size);
	int max = max_index(array, size);
	if (min > max)
		std::swap(min, max);
	T sum = 0;
	for (int i = min; i <= max; i++)
		sum += array[i];
	return sum;
}

double sum(double* array, int size)
{
	int min = min_index(array, size);
	int sum = 0;
	for (int i = 0; i <= min; i++)
		sum += array[i];
	return sum;
}

template<class T>
void printArray(T* array, int size)
{
	for (int i = 0; i < size; i++)
		std::cout << array[i] << " ";
	std::cout << std::endl;
}

int main()
{
	setlocale(0, "russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));
	int* iArray;
	double* dArray;
	int size;
	std::cout << "Введите размер массива: ";
	std::cin >> size;
	iArray = initialisation<int>(size);
	dArray = initialisation<double>(size);

	printArray(iArray, size);
	std::cout << "Sum:" << sum(iArray, size) << std::endl;

	printArray(dArray, size);
	std::cout << "Sum:" << sum(dArray, size) << std::endl;
	delete[] iArray;
	delete[] dArray;
	return 0;
}