#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <string.h>

#define N 5
#define N2 10
#define M2 12


int main()
{
	setlocale(0, "russian");
	time_t k;
	srand(time(&k));
	int run = 1, c;

	while (run)
	{
		printf("1.Задание 1\n");
		printf("2.Задание 2\n");
		printf("3.Выход\n");
		printf("Введите номер задания: ");
		scanf("%d", &c);

		if (c == 1)
		{
			int arr[N], sumPositive = 0, sumNegative = 0;

			for (int i = 0; i < N; i++)
				arr[i] = rand() * (rand() % 2 ? 1 : -1);

			for (int i = 0; i < N; i++)
				printf("%d ", arr[i]);
			printf("\n");

			int max = arr[0];
			int maxIndex = 0;
			for (int i = 1; i < N; i++)
				if (arr[i] > max)
				{
					max = arr[i];
					maxIndex = i;
				}

			for (int i = 0; i < maxIndex; i++)
				if (arr[i] < 0)
					sumNegative += arr[i];

			for (int i = maxIndex + 1; i < N; i++)
				if (arr[i] > 0)
					sumPositive += arr[i];

			printf("Максимальный элемент: %d\n", max);
			printf("Сумма положительных элементов после максимума: %d\n", sumPositive);
			printf("Сумма отрицательных элементов до максимума: %d\n", sumNegative);
		}
		else if (c == 2)
		{
			int matrix[N2][M2];
			int countPositive = 0;
			int countNegative[M2 / 2];
			
			for (int i = 0; i < M2 / 2; i++)
				countNegative[i] = 0;

			for (int i = 0; i < N2; i++)
				for (int j = 0; j < M2; j++)
					matrix[i][j] = rand() * (rand() % 2 ? -1 : 1);

			for (int i = 0; i < N2; i++)
			{
				for (int j = 0; j < M2; j++)
					printf("%d\t", matrix[i][j]);
				printf("\n");
			}

			for (int i = N2 / 2; i < N2; i++)
				for (int j = 0; j < M2; j++)
					if (matrix[i][j] > 0)
						countPositive++;

			printf("Количество положительных элементов в заштрихованной области: %d\n", countPositive);

			for (int j = 1; j < M2; j += 2)
				for (int i = 0; i < N2; i++)
					if (matrix[i][j] < 0)
						countNegative[j / 2]++;

			printf("Количество отрицательных элементов в четных столбцах(нумерация с 1):\n");
			for (int i = 0; i < M2 / 2; i++)
				printf("%d ", countNegative[i]);
			printf("\n");
		}
		else if (c == 3)
		{
			run = 0;
		}
	}


	return 0;
}