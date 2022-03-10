#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define N 2049

char* InputString()
{
	printf("Enter string: ");
	char buff[N];
	char* str;
	scanf("%s", &buff);
	str = (char*)malloc(strlen(buff) + 1);
	strcpy(str, buff);

	return str;
}

char* DeleteChar(char* str)
{
	int count = 0;
	int* index = (int*)malloc(0);
	for (int i = strlen(str) - 1; i >= 0; i--)
	{
		for(int j = i+1; j < strlen(str);j++)
			if (str[i] == str[j])
			{
				count++;
				index = (int*)realloc(index, sizeof(int) * count);
				index[count - 1] = i;
				break;
			}
	}

	char* newStr = (char*)malloc((strlen(str) - count + 1) * sizeof(char));
	int flag = 0, k = 0;
	for (int i = 0; i < strlen(str); i++)
	{
		flag = 0;
		for (int j = 0; j < count; j++)
			if (str[i] == str[index[j]])
			{
				flag = 1;
				break;
			}
		if (!flag)
		{
			newStr[k] = str[i];
			k++;
		}
	}

	newStr[k] = '\0';
	return newStr;
}

char* DeleteNumber(char* str)
{
	int count = 0;
	int* numb = (int*)malloc(0 * sizeof(int));
	for (int i = 0; i < strlen(str); i++)
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

int Sum(int** matr, int row, int col)
{
	int sum = 0;
	for (int j = 0; j < col / 2; j++)
		for (int i = j; i < row - j; i++)
			sum += matr[i][j];

	for (int j = col / 2; j < col; j++)
		for (int i = row - j - 1; i < j + 1; i++)
			sum += matr[i][j];

	return sum;
}

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
		if (buff[strlen(buff) - 1] == 'h' && buff[strlen(buff) - 2] == 's' && buff[strlen(buff) - 3] == 'i' && buff[strlen(buff) - 4] == 'n' && buff[strlen(buff) - 5] == 'i' && buff[strlen(buff) - 6] == 'f')
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

int MaxLenth(int* lenth, int size, int max)
{
	int* arr = (int*)malloc(sizeof(int) * size);
	for (int i = 0; i < size; i++)
		arr[i] = lenth[i];
	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++)
			if (arr[i] < arr[j])
			{
				int tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}

	return arr[max - 1];
}

void PrintText(char** text, int size, int numberCount)
{
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		int countWords = 0;
		char** words = malloc(0);
		words = FindWord(text[i], words, &countWords);
		int* lenth = (int*)malloc(sizeof(int) * countWords);
		for (int j = 0; j < countWords - 1; j++)
			lenth[j] = (*(words + j + 1) - *(words + j)) - 1;
		lenth[countWords - 1] = (text[i] + strlen(text[i])) - *(words + countWords - 1);

		count = 0;
		int maxLenth = MaxLenth(lenth, countWords, numberCount);
		for (int j = 0, k = 0; j < strlen(text[i]); j++)
		{
			if (text[i] + j == words[k])
			{
				if (lenth[k] <= maxLenth && count < numberCount)
				{
					for(int l = 0; l < lenth[k]; l++)
					{
						printf("%c", text[i][j]);
						j++;
					}
					count++;
					printf(" ");
				}
				k++;
			}
		}
		printf("\n");
	}
}

double* InitArray(int n, int m)
{
	double* arr = (double*)malloc(n * m * sizeof(double));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			*(arr + i * m + j) = (rand() % 10 + (double)rand() / 0x7fff) * (rand() % 2 ? -1 : 1);

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


double** FindNegativeElement(double* matr, int row, int col, int *count)
{
	*count = 0;
	double** ptrNeg = (double**)malloc(0);

	for (int j = 0; j < col / 2; j++)
		for (int i = j; i < row - j; i++)
			if (*(matr + row * i + j) < 0)
			{
				(*count)++;
				ptrNeg = (double**)realloc(ptrNeg,(*count) * sizeof(double*));
				ptrNeg[(*count) - 1] = (matr + row * i + j);
			}

	for (int j = col / 2; j < col; j++)
		for (int i = row - j - 1; i < j + 1; i++)
			if (*(matr + row * i + j) < 0)
			{
				(*count)++;
				ptrNeg = (double**)realloc(ptrNeg,(*count) * sizeof(double*));
				ptrNeg[(*count) - 1] = (matr + row * i + j);
			}

	return ptrNeg;
}


int main()
{
	setlocale(0, "russian");
	time_t k;
	srand(time(&k));
	int run = 1, c;

	while (run)
	{
		printf("\n1.Level 1 Exersise 1");
		printf("\n2.Level 1 Exersise 2");
		printf("\n3.Level 2 Exersise 1");
		printf("\n4.Level 2 Exersise 2");
		printf("\n5.Exit");
		printf("\nEnter command number: ");
		scanf("%d", &c);

		if (c == 1)
		{
			char* strA = InputString();
			char* strB = InputString();

			printf("\nString À: ");
			printf("%s", strA);
			printf("\nString B: ");
			printf("%s", strB);

			strA = DeleteNumber(strA);
			strB = DeleteChar(strB);


			printf("\nChanged string À: ");
			printf("%s", strA);
			printf("\nChanged string B: ");
			printf("%s", strB);

			free(strA);
			free(strB);

		}
		else if (c == 2)
		{
			int N2, M2;
			int** matrix;
			int sum;
			printf("Enter number of row: ");
			scanf("%d", &N2);
			printf("Enter number of column: ");
			scanf("%d", &M2);

			matrix = InitMatrix(N2, M2);

			PrintMatrix(matrix, N2, M2);

			sum = Sum(matrix, N2, M2);

			printf("\nSum in the highlighted area: %d", sum);

			for (int i = 0; i < N2; i++)
				free(matrix[i]);
			free(matrix);

		}
		else if (c == 3)
		{
			char** text;
			int size, numberCount;

			text = InputText(&size);

			printf("\nEnter number of word in row: ");
			scanf("%d", &numberCount);

			PrintText(text, size, numberCount);

			free(text);
		}
		else if (c == 4)
		{
			int N2, M2;
			double* matrix;
			double** negativePtr;
			int size;
			printf("Enter number of row: ");
			scanf("%d", &N2);
			printf("Enter number of column: ");
			scanf("%d", &M2);

			matrix = InitArray(N2, M2);

			PrintArray(matrix, N2, M2);

			negativePtr = FindNegativeElement(matrix, N2, M2, &size);

			printf("\nPointers to negative elements: ");
			for (int i = 0; i < size; i++)
				printf("%p ", negativePtr[i]);

			printf("\nNegative elements: ");
			for (int i = 0; i < size; i++)
				printf("%fe ", *(negativePtr[i]));

			free(matrix);
			free(negativePtr);

		}
		else if (c == 5)
		{
			run = 0;
		}
	}

	return 0;
}