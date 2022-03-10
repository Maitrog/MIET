#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cctype>
#include <ctime>

char** InputString(int* size)
{
	const int N = 2049;

	char buff[N];
	char** str;
	(*size) = 0;
	str = (char**)malloc(sizeof(char*));
	std::cout << "Введите текст" << std::endl;
	for (int i = 0; ; i++)
	{
		str = (char**)realloc(str, sizeof(char*) * (i + 1));
		std::cin >> buff;
		str[i] = (char*)malloc(strlen(buff) + 1);
		strcpy(str[i], buff);
		(*size)++;
		if (buff[strlen(buff) - 1] == 'k' && buff[strlen(buff) - 2] == 'o')
			break;
	}
	return str;
}

void Cheker(int* printedCharactersNumber, int* printedStringsNumber, int charCount, int stringCount) 
{
	if (*printedCharactersNumber == charCount)
	{
		std::cout << std::endl;
		(*printedCharactersNumber) = 0;
		(*printedStringsNumber)++;
	}
	if (*printedStringsNumber == stringCount)
	{
		std::cout << std::endl;
		(*printedStringsNumber) = 0;
	}
}

char** NumberFound(char** str, int* numberCount, int strSize)
{
	char** mas = (char**)malloc(sizeof(char*));
	*numberCount = 0;
	for (int i = 0; i < strSize; i++)
		for (int j = 0; j < strlen(str[i]); j++)
			if (isdigit(str[i][j]))
			{
				mas = (char**)realloc(mas, sizeof(char*) * (*numberCount + 1));
				*(mas + *numberCount) = (*(str + i) + j);
				(*numberCount)++;
			}
	return mas;
}

void PrintString(char** str, int strSize, int charCount, int stringCount)
{
	int count_c = 0, count_str = 0;
	int size_A, p = 0;
	char** A, *ptrA;
	A = NumberFound(str, &size_A, strSize);
	ptrA = A[p];
	std::cout << std::endl;
	for (int i = 0; i < strSize; i++)
	{
		for (int j = 0; j < strlen(str[i]); j++)
		{
			if (str[i]+j == ptrA) //проверяем является ли символ числом
			{
				if ((int)(str[i][j] - '0') % 2 == 0)
				{
					int num = (int)(str[i][j] - '0') * 2;
					if (num < 10)
					{
						std::cout << num;
						count_c++;
						Cheker(&count_c, &count_str, charCount, stringCount);
					}
					else
					{
						std::cout << num / 10;
						count_c++;
						Cheker(&count_c, &count_str, charCount, stringCount);
						std::cout << num % 10;
						count_c++;
						Cheker(&count_c, &count_str, charCount, stringCount);
					}

				}
				if (p < size_A)
				{
					p++;
					ptrA = A[p];
				}
			}
			else
			{
				std::cout << str[i][j];
				count_c++;
				Cheker(&count_c, &count_str, charCount, stringCount);
			}
		}
	}
}

double* InitArray(int n, int m)
{
	double* arr = (double*)malloc(n * m * sizeof(double));
	for(int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			*(arr + i * m + j) = rand() % 10 + (double)rand() / RAND_MAX;

	return arr;
}

void PrintArray(double* arr, int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			std::cout << *(arr + i * m + j) << " ";
		std::cout << std::endl;
	}
}

double** MinFound(double* arr, int n, int m, int* count_min)
{
	double** mas_min = (double**)malloc(sizeof(double*));
	double min = *arr;
	for (int i = 0; i < n / 2; i++)//Поиск в верхнем треугольнике
	{
		for (int j = i; j < m - i; j++)
			if (*(arr + i * m + j) == min)
			{
				mas_min = (double**)realloc(mas_min, sizeof(double*) * (*count_min + 1));
				*(mas_min + *count_min) = (arr + i * m + j);
				(*count_min)++;
			}
			else
				if (*(arr + i * m + j) < min)
				{
					min = *(arr + i * m + j);
					(*count_min) = 1;
					free(mas_min);
					mas_min = (double**)malloc(sizeof(double*) * (*count_min));
					(*(mas_min)) = (arr + i * m + j);
				}
	}
	for (int i = n / 2; i < n; i++)//Поиск в нижнем треугольнике
	{
		for (int j = n - i - 1; j < i + 1; j++)
			if (*(arr + i * m + j) == min)
			{
				mas_min = (double**)realloc(mas_min, sizeof(double*) * (*count_min + 1));
				*(mas_min + *count_min) = (arr + i * m + j);
				(*count_min)++;
			}
			else
				if (*(arr + i * m + j) < min)
				{
					min = *(arr + i * m + j);
					(*count_min) = 1;
					free(mas_min);
					mas_min = (double**)malloc(sizeof(double*) * (*count_min));
					(*(mas_min)) = (arr + i * m + j);
				}
	}
	return mas_min;
}

int main()
{
	setlocale(0, "russian");
	int c;
	time_t k;
	srand(time(&k));
	std::cout << "1.Задание 1" << std::endl;
	std::cout << "2.Задание 2" << std::endl;
	std::cin >> c;
	if (c == 1)
	{
		char** str;
		int size_A, strSize;
		char** A;
		str = InputString(&strSize);
		int stringCount, charCount;
		std::cout << "Введите параметры форматирования\nКоличество строк: ";
		std::cin >> stringCount;
		std::cout << "Количество символов в строке: ";
		std::cin >> charCount;
		PrintString(str, strSize, charCount, stringCount);

		for (int i = 0; i < strSize; i++)
			free(str[i]);
		free(str);
	}
	else if (c == 2)
	{
		const int N = 10, M = 10;
		double* A, ** masMin;
		int masMinSize = 0;
		A = InitArray(N, M);
		PrintArray(A, N, M);
		masMin = MinFound(A, N, M, &masMinSize);

		std::cout << std::endl << "Минимальные элементы: " << std::endl;
		for (int i = 0; i < masMinSize; i++)
			std::cout << "Адрес: " << masMin[i] << " Значение: " << *(masMin[i]) << std::endl;

		free(A);
	}
	return 0;
}