#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <Windows.h>

struct Car
{
	char* brand;
	char* ownerSurname;
	char* ownerName;
	int	enginePower;
	int mileage;
};

struct Car CreateCar()
{
	struct Car newCar;
	char buff[26];
	printf("\nВведите марку машины: ");
	scanf("%25s", buff);
	newCar.brand = (char*)malloc((strlen(buff) + 1) * sizeof(char));
	strcpy(newCar.brand, buff);

	printf("Введите фамилию владельца: ");
	scanf("%25s", buff);
	newCar.ownerSurname = (char*)malloc((strlen(buff) + 1) * sizeof(char));
	strcpy(newCar.ownerSurname, buff);

	printf("Введите имя владельца: ");
	scanf("%25s", buff);
	newCar.ownerName = (char*)malloc((strlen(buff) + 1) * sizeof(char));
	strcpy(newCar.ownerName, buff);

	printf("Введите мощность двигателя: ");
	scanf("%d", &newCar.enginePower);

	printf("Введите пробег машины: ");
	scanf("%d", &newCar.mileage);

	return newCar;
}

void PrintTable(struct Car* cars, int carsCount)
{
	if (carsCount > 0)
	{
		printf("%-26s%-26s%-26s%-26s%s", "Марка машины", "Фамилия", "Имя", "Мощность двигателя", "Пробег\n");
		printf("--------------------------------------------------------------------------------------------------------------\n");
		for (int i = 0; i < carsCount; i++)
		{
			printf("%-26s%-26s%-26s%-26d%d\n", cars[i].brand, cars[i].ownerSurname, cars[i].ownerName, cars[i].enginePower, cars[i].mileage);
		}
	}
}

void FindByBrand(struct Car* cars, int carsCount, char* brand)
{
	struct Car* tmpCar = (struct Car*)malloc(0);
	int count = 0;

	for (int i = 0; i < carsCount; i++)
	{
		if (strcmp(brand, cars[i].brand) == 0)
		{
			count++;
			tmpCar = (struct Car*)realloc(tmpCar, sizeof(struct Car) * count);
			tmpCar[count - 1] = cars[i];
		}
	}

	if (count > 0)
		PrintTable(tmpCar, count);
	else
		printf("Машин такой марки не найдено\n");

	free(tmpCar);
}

struct Car* SortByOwner(struct Car* cars, int carsCount)
{
	for (int i = 0; i < carsCount - 1; i++)
		for (int j = 0; j < carsCount - 1; j++)
			if (strcmp(cars[j].ownerSurname, cars[j + 1].ownerSurname) == 1 || (strcmp(cars[j].ownerSurname, cars[j + 1].ownerSurname) == 0 && strcmp(cars[j].ownerName, cars[j + 1].ownerName) == 1))
			{
				struct Car tmp = cars[j];
				cars[j] = cars[j + 1];
				cars[j + 1] = tmp;
			}

	return cars;
}

void FindByMileage(struct Car* cars, int carsCount, int milleage)
{
	struct Car* tmpCar = (struct Car*)malloc(0);
	int count = 0;

	for (int i = 0; i < carsCount; i++)
	{
		if (cars[i].mileage > milleage)
		{
			count++;
			tmpCar = (struct Car*)realloc(tmpCar, sizeof(struct Car) * count);
			tmpCar[count - 1] = cars[i];
		}
	}

	tmpCar = SortByOwner(tmpCar, count);
	PrintTable(tmpCar, count);

	free(tmpCar);
}



int main()
{
	setlocale(0, "russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	struct Car* cars = (struct Car*)malloc(0);
	int count = 0;
	char buff[100];
	int intBuff;
	int c;
	int exit = 1;
	while (exit)
	{
		printf("1.Добавить машину\n");
		printf("2.Распечатать информацию о машинах\n");
		printf("3.Найти машины по марке\n");
		printf("4.Найти владельцев с пробегом машин больше заданного\n");
		printf("5.Выход\n");
		printf("Введите команду: ");

		scanf("%d", &c);
		
		switch (c)
		{
		case 1:
			count++;
			cars = (struct Car*)realloc(cars, sizeof(struct Car) * count);
			cars[count - 1] = CreateCar();
			break;
		case 2:
			PrintTable(cars, count);
			break;
		case 3:
			printf("\nВведите марку машины: ");
			scanf("%s100", buff);
			FindByBrand(cars, count, buff);
			break;
		case 4:
			printf("\nВведите пробег машины: ");
			scanf("%d", &intBuff);
			FindByMileage(cars, count , intBuff);
			break;
		case 5:
			exit = 0;
		default:
			break;
		}
	}

	free(cars);
}