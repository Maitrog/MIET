#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <Windows.h>

#define N 2049

char** InputText(int* size)
{
	char buff[N];
	char** str;
	(*size) = 0;
	str = (char**)malloc(sizeof(char*));
	printf("Enter text:\n");

	for (int i = 0; ; i++)
	{
		str = (char**)realloc(str, sizeof(char*) * (i + 1));
		gets(buff);
		str[i] = (char*)malloc(strlen(buff) + 1);
		strcpy(str[i], buff);
		(*size)++;
		if (buff[strlen(buff) - 1] == 'o' && buff[strlen(buff) - 2] == 'n')
			break;
	}
	return str;
}

char** FindWord(char* str, char** words, int* countWord)
{
	words = (char**)malloc(0);
	*countWord = 0;
	if (!isspace(str[0]))
	{
		(*countWord)++;
		words = (char**)realloc(words, sizeof(char*) * *countWord);
		words[*countWord - 1] = str;
	}

	for (int j = 1; j < strlen(str); j++)
	{
		if (!isspace(str[j]) && isspace(str[j - 1]))
		{
			(*countWord)++;
			words = (char**)realloc(words, sizeof(char*) * *countWord);
			words[*countWord - 1] = str + j;
		}
	}

	return words;
}

int Equal(char* str1, char* str2)
{
	int k = 0;
	for (; (!isspace(*(str2 + k)) && *(str2 + k) != '\0') || !isspace(*(str1 + k)); k++)
		if (*(str1 + k) != *(str2 + k))
			return 0;

	return 1;
}

int Contains(char** input, int size, char* elem)
{
	for (int i = 0; i < size; i++)
	{
		if (input[i] == elem)
			return 1;
	}

	return 0;
}

char** EqualWords(char** words, int size, char** equalWords, int* countEqualWord)
{
	*countEqualWord = 0;
	for (int j = 0; j < size - 1; j++)
		for (int k = j + 1; k < size; k++)
		{
			if (Equal(words[j], words[k]))
			{
				if (!Contains(equalWords, *countEqualWord, words[j]))
				{
					(*countEqualWord)++;
					equalWords = (char**)realloc(equalWords, (*countEqualWord) * sizeof(char*));
					equalWords[*countEqualWord - 1] = words[j];
				}

				if (!Contains(equalWords, *countEqualWord, words[k]))
				{
					(*countEqualWord)++;
					equalWords = (char**)realloc(equalWords, (*countEqualWord) * sizeof(char*));
					equalWords[*countEqualWord - 1] = words[k];
				}
			}
		}

	return equalWords;
}

void PrintText(char** text, int size)
{
	int maxLenght = 0;
	for (int i = 0; i < size; i++)
	{
		if (strlen(text[i]) > maxLenght)
			maxLenght = strlen(text[i]);
	}
	for (int i = 0; i < size; i++)
	{
		int Tab = (maxLenght - strlen(text[i])) / 2;
		int countWord = 0;
		int countEqualWord = 0;
		char** words = (char**)malloc(0);
		char** equalWords = (char**)malloc(0);
		words = FindWord(text[i], words, &countWord);
		equalWords = EqualWords(words, countWord, equalWords, &countEqualWord);

		printf("%-*s", Tab, "");

		for (int j = 0; j < countWord; j++)
			if (Contains(equalWords, countEqualWord, words[j]))
			{
				for (int l = 0; l < (j != (countWord - 1) ? (words[j + 1] - words[j]) : (text[i] + strlen(text[i])  - words[j])); l++)
					printf("%c", (char)toupper(words[j][l]));
			}
			else
			{
				for (int l = 0; l < (j != (countWord - 1) ? (words[j + 1] - words[j]) : (text[i] + strlen(text[i]) - words[j])); l++)
					printf("%c", words[j][l]);
			}
		printf("\n");
	}
}


double* InitArray(int n, int m)
{
	double* arr = (double*)malloc(n * m * sizeof(double));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			*(arr + i * m + j) = (rand() % 10 /*+ (double)rand() / 0x7fff*/) * (rand() % 2 ? -1 : 1);

	return arr;
}

void PrintArray(double* arr, int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			printf("%fe ", *(arr + i * m + j));
		printf("\n");
	}
}

double** FindZero(double* matr, int row, int col, int* count)
{
	*count = 0;
	double** ptrZero = (double**)malloc(0);

	for(int i = row/2; i<row; i++)
		for(int j = 0; j < col; j++)
			if (*(matr + row * i + j) == 0)
			{
				(*count)++;
				ptrZero = (double**)realloc(ptrZero, (*count) * sizeof(double*));
				ptrZero[(*count) - 1] = (matr + row * i + j);
			}

	return ptrZero;
}

int main()
{
	setlocale(0, "russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	time_t k;
	srand(time(&k));
	int run = 1, c;

	while (run)
	{
		printf("\n1.Level 2 Exersise 1");
		printf("\n2.Level 2 Exersise 2");
		printf("\n3.Exit");
		printf("\nEnter command number: ");
		scanf("%d", &c);

		if (c == 1)
		{
			char** text;
			int size;

			text = InputText(&size);

			PrintText(text, size);

			free(text);
		}
		else if (c == 2)
		{
			int N2, M2;
			double* matrix;
			double** zeroPtr;
			int size;
			printf("Enter number of row: ");
			scanf("%d", &N2);
			printf("Enter number of column: ");
			scanf("%d", &M2);

			matrix = InitArray(N2, M2);

			PrintArray(matrix, N2, M2);

			zeroPtr = FindZero(matrix, N2, M2, &size);

			printf("\nPointers to zero elements: ");
			for (int i = 0; i < size; i++)
				printf("%p ", zeroPtr[i]);

			printf("\Zero elements: ");
			for (int i = 0; i < size; i++)
				printf("%fe ", *(zeroPtr[i]));

			free(matrix);
			free(zeroPtr);

		}
		else if (c == 3)
		{
			run = 0;
		}
	}
	return 0;
}