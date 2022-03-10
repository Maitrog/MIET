#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define N 2049

char* InputString()
{
	printf("Введите строку: ");
	char buff[N];
	char* str;
	scanf("%s", &buff);
	str = (char*)malloc(strlen(buff) + 1);
	strcpy(str, buff);
	
	return str;
}

char* DeleteNumber(char* str)
{
	int count = 0;
	int* numb = (int*)malloc(0 * sizeof(int));
	for(int i = 0; i < strlen(str); i++)
		if ((str[i]) >= '0' && str[i] <= '9')
		{
			count++;
			numb = (int*)realloc(numb, count * sizeof(int));
			numb[count - 1] = i;
		}
	char* newStr = (char*)malloc((strlen(str) - count + 1) * sizeof(char));
	for (int i = 0, j = 0, k = 0; i < strlen(str); i++)
		if (i != numb[j])
		{
			newStr[k] = str[i];
			k++;
		}
		else
			j++;

	newStr[(strlen(str) - count)] = '\0';
	return newStr;
}

int CountLowercaseLetter(char* str)
{
	int count = 0;
	for (int i = 0; i < strlen(str); i++)
		if (isalpha(str[i]) && islower(str[i]))
			count++;

	return count;
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

int CountNegative(int** matr, int row, int col)
{
	int count = 0;
	for (int j = 0; j < col / 2; j++)
		for (int i = j; i < row - j; i++)
			if (matr[i][j] < 0)
				count++;

	for (int j = col / 2; j < col; j++)
		for (int i = row - j - 1; i < j + 1; i++)
			if (matr[i][j] < 0)
				count++;

	return count;
}

char** InputText(int* size)
{
	char buff[N];
	char** str;
	(*size) = 0;
	str = (char**)malloc(sizeof(char*));
	printf("Введите текст\n");
	for (int i = 0; ; i++)
	{
		str = (char**)realloc(str, sizeof(char*) * (i + 1));
		scanf("%s", &buff);
		str[i] = (char*)malloc(strlen(buff) + 1);
		strcpy(str[i], buff);
		str[i][strlen(buff) + 1] = '\0';
		(*size)++;
		if (buff[strlen(buff) - 1] == 's' && buff[strlen(buff) - 2] == 'e' && buff[strlen(buff) - 3] == 'y')
			break;
	}
	return str;
}

char** FindWord(char** text, int size, char** words, int *countWord)
{
	words = (char**)malloc(0);
	*countWord = 0;
	for (int i = 0; i < size; i++)
	{	
		if (!isspace(text[i][0]))
		{
			(*countWord)++;
			words = (char**)realloc(words, sizeof(char*) * *countWord);
			words[*countWord - 1] = text[i];
		}
		for (int j = 1; j < strlen(text[i]); j++)
		{
			if(!isspace(text[i][j]) && isspace(text[i][j-1]))
			{
				(*countWord)++;
				words = (char**)realloc(words, sizeof(char*) * *countWord);
				words[*countWord - 1] = text[i][j];
			}
		}
	}

	return words;
}

void PrintText(char** text, int size, char** word, int countWord)
{
	int row = 1;
	int wordInRow = 0;
	int p = 0;
	char* ptrW = word[p];
	for(int i = 0; i < size; i++)
		for (int j = 0; j < strlen(text[i]); j++)
		{
			if (text[i] + j == ptrW)
			{
				if (row % 2 == 1)
				{
					printf("%s", text[i]);
					printf("%s", text[i]);

				}
				else
				{
					printf("+");
					printf("%s", text[i]);
				}
				p++;
				ptrW = word[p];
				wordInRow++;
				printf(" ");
				if (wordInRow == row)
				{
					row++;
					wordInRow = 0;
					printf("\n");
				}
			}
			/*else
			{
				printf("%c", text[i][j]);
			}*/
		}
}

double* InitArray(int n, int m)
{
	double* arr = (double*)malloc(n * m * sizeof(double));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			*(arr + i * m + j) = rand() % 10 + (double)rand() / 0x7fff;

	return arr;
}

void PrintArray(double* arr, int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			printf("%fe ",*(arr + i * m + j));
		printf("\n");
	}
}


double* FindMinMax(double* matr, int row, int col)
{
	double min = _CRT_INT_MAX;
	double max = -_CRT_INT_MAX;
	
	for (int j = 0; j < col / 2; j++)
		for (int i = j; i < row - j; i++)
			if (*(matr + row * i + j) < min)
				min = *(matr + row * i + j);

	for (int j = col / 2; j < col; j++)
		for (int i = row - j - 1; i < j + 1; i++)
			if (*(matr + row * i + j) > max)
				max = *(matr + row * i + j);

	double* MinMax = (double*)malloc(sizeof(double) * 2);
	MinMax[0] = min;
	MinMax[1] = max;

	return MinMax;
}


int main()
{
	setlocale(0, "russian");
	time_t k;
	srand(time(&k));
	int run = 1, c;

	while (run)
	{
		printf("\n1.Уровень 1 Задание 1");
		printf("\n2.Уровень 1 Задание 2");
		printf("\n3.Уровень 2 Задание 1");
		printf("\n4.Уровень 2 Задание 2");
		printf("\n5.Выход");
		printf("\nВведите номер задания: ");
		scanf("%d", &c);

		if (c == 1)
		{
			char* strA = InputString();
			char* strB = InputString();

			printf("\nСтрока А: ");
			printf("%s", strA);
			printf("\nСтрока B: ");
			printf("%s", strB);

			strA = DeleteNumber(strA);
			strB = DeleteNumber(strB);


			printf("\nИзменённая строка А: ");
			printf("%s", strA);
			printf("\nИзменённая строка B: ");
			printf("%s", strB);

			int countA = CountLowercaseLetter(strA);
			int countB = CountLowercaseLetter(strB);

			printf("\nКоличество строчных букв в строке А: ");
			printf("%d", countA);
			printf("\nКоличество строчных букв в строке B: ");
			printf("%d", countB);

			free(strA);
			free(strB);

		}
		else if (c == 2)
		{
			int N2, M2;
			int** matrix;
			int countNegative;
			printf("Введите количество строк: ");
			scanf("%d", &N2);
			printf("Введите количество столбцов: ");
			scanf("%d", &M2);

			matrix = InitMatrix(N2, M2);

			PrintMatrix(matrix, N2, M2);

			countNegative = CountNegative(matrix, N2, M2);

			printf("\nКоличество отрицательных элементов в заштрихованной области: %d", countNegative);

			for (int i = 0; i < N2; i++)
				free(matrix[i]);
			free(matrix);

		}
		else if (c == 3)
		{
			char** text, ** word = NULL;
			int size, countWord;

			text = InputText(&size);

			word = FindWord(text, size, word, &countWord);

			PrintText(text, size, word, countWord);

			free(text);
		}
		else if (c == 4)
		{
			int N2, M2;
			double* matrix;
			double* minMax;
			printf("Введите количество строк: ");
			scanf("%d", &N2);
			printf("Введите количество столбцов: ");
			scanf("%d", &M2);

			matrix = InitArray(N2, M2);

			PrintArray(matrix, N2, M2);

			minMax = FindMinMax(matrix, N2, M2);

			printf("\nМинимальный элемент в левой части заштрихованной области: %fe", minMax[0]);
			printf("\nМаксимальный элемент в правой части заштрихованной области: %fe", minMax[1]);

			free(matrix);
			free(minMax);

		}
		else if (c == 5)
		{
			run = 0;
		}
	}

	return 0;
}