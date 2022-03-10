#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <math.h>

#define N 5
#define M 5


int main()
{
	setlocale(0, "russian");
	/*
	time_t k;
	srand(time(&k));
	int X[N],max=-24000000,count=0, minus;
	for (int i = 0; i < N; i++)
	{
		minus = rand();
		X[i] = rand()*(minus%2==1?1:-1);
		if (X[i] % 2 == 0)
		{
			if (X[i] > max)
				max = X[i];
		}
		else
			count++;
	}
	printf("Максимальное четное число %d\n", max);
	printf("Колличество нечетных чисел: %d\n", count);
	for (int i = 0; i < N; i++)
		printf("%d\t", X[i]);
	*/
	
	///*
	time_t k;
	srand(time(&k));
	int X[N][M], nuls = 0, positive = 0,minus, arrMin[M];
	for (int i = 0; i < M; i++)
		arrMin[i] = 24000000;
	for(int i=0;i<N;i++)
		for (int j = 0; j < M; j++)
		{
			minus = rand();
			X[i][j] = rand() * (minus % 2 == 1 ? 1 : -1);
		}
	for (int i = 0; i < N / 2 + N % 2 == 1 ? 1 : 0; i++)
	{
		for (int j = i; j < M - i; j++)
			nuls += X[i][j] == 0 ? 1 : 0;
	}
	for (int i = N/2; i < N; i++)
	{
		for (int j = M-(i+1); j < i+1; j++)
			positive += X[i][j] > 0 ? 1 : 0;
	}
	for (int j = 0; j < M; j++)
		for (int i = 0; i < N; i++)
			arrMin[j] = abs(X[i][j]) < arrMin[j] ? abs(X[i][j]):arrMin[j];
	printf("Количество нулей: %d\n", nuls);
	printf("Количество положительных чисел: %d\n", positive);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
			printf("%10d", X[i][j]);
		printf("\n");
	}
	printf("\n");
	for (int i = 0; i < M; i++)
		printf("%10d", arrMin[i]);
		//*/
	return 0;
}