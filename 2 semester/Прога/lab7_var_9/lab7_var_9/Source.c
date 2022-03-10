#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <time.h>

struct Fio
{
	char* surname;
	char* name;
	char* secondname;
};

struct Date
{
	int day;
	char* month;
	int year;
};

struct Car
{
	struct Fio owner;
	char* brand;
	int	enginePower;
	int mileage;
	struct Date lastTO;
};

struct Car CreateCar()
{
	struct Car newCar = { { "", "", "" }, "", 0, 0 };
	char buff[26];
	printf("\nВведите марку машины: ");
	scanf("%25s", buff);
	newCar.brand = (char*)malloc((strlen(buff) + 1) * sizeof(char));
	strcpy(newCar.brand, buff);

	printf("Введите фамилию владельца: ");
	scanf("%25s", buff);
	newCar.owner.surname = (char*)malloc((strlen(buff) + 1) * sizeof(char));
	strcpy(newCar.owner.surname, buff);

	printf("Введите имя владельца: ");
	scanf("%25s", buff);
	newCar.owner.name = (char*)malloc((strlen(buff) + 1) * sizeof(char));
	strcpy(newCar.owner.name, buff);

	printf("Введите отчество владельца: ");
	scanf("%25s", buff);
	newCar.owner.secondname = (char*)malloc((strlen(buff) + 1) * sizeof(char));
	strcpy(newCar.owner.secondname, buff);

	printf("Введите мощность двигателя: ");
	scanf("%d", &newCar.enginePower);

	printf("Введите пробег машины: ");
	scanf("%d", &newCar.mileage);

	printf("Введите дату последнего ТО\n");
	printf("День: ");
	scanf("%d", &newCar.lastTO.day);

	printf("Месяц (Jan/Янв, Feb/Фев, Mar/Мар, Apr/Апр, May/Май, June/Июнь, July/Июль, Aug/Авг, Sept/Сен, Oct/Окт, Nov/Ноя, Dec/Дек): ");
	scanf("%25s", buff);
	newCar.lastTO.month = (char*)malloc((strlen(buff) + 1) * sizeof(char));
	strcpy(newCar.lastTO.month, buff);

	printf("Год: ");
	scanf("%d", &newCar.lastTO.year);

	return newCar;
}

void PrintTable(struct Car* cars, int carsCount)
{
	if (carsCount > 0)
	{
		printf("%-26s%-26s%-26s%-26s%-20s%-8s%s", "Марка машины", "Фамилия", "Имя", "Отчество", "Мощность двигателя", "Пробег", "Дата последнего ТО\n");
		printf("----------------------------------------------------------------------------------------------------------------------------------------------------\n");
		for (int i = 0; i < carsCount; i++)
		{
			printf("%-26s%-26s%-26s%-26s%-20d%-8d%d %s %d\n", cars[i].brand, cars[i].owner.surname, cars[i].owner.name, cars[i].owner.secondname, cars[i].enginePower, 
				cars[i].mileage, cars[i].lastTO.day, cars[i].lastTO.month, cars[i].lastTO.year);
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
			if (strcmp(cars[j].owner.surname, cars[j + 1].owner.surname) == 1 || (strcmp(cars[j].owner.surname, cars[j + 1].owner.surname) == 0 && strcmp(cars[j].owner.name, 
				cars[j + 1].owner.name) == 1) || (strcmp(cars[j].owner.surname, cars[j + 1].owner.surname) == 0 && strcmp(cars[j].owner.name, cars[j + 1].owner.name) == 0 && 
					strcmp(cars[j].owner.secondname, cars[j + 1].owner.secondname) == 1))
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

void LastTOCar(struct Car* cars, int carsCount)
{
	time_t t = time(0);
	struct tm* now = localtime(&t);
	double time = 0.0;
	struct Car* tmpCar = (struct Car*)malloc(0);
	int count = 0;
	
	for (int i = 0; i < carsCount; i++)
	{
		int day = cars[i].lastTO.day;
		int month = -1;
		int year = cars[i].lastTO.year;
		if (strcmp(cars[i].lastTO.month, "Jan") == 0 || strcmp(cars[i].lastTO.month, "Янв") == 0)
			month = 1;
		else if (strcmp(cars[i].lastTO.month, "Feb") == 0 || strcmp(cars[i].lastTO.month, "Фев") == 0)
			month = 2;
		else if (strcmp(cars[i].lastTO.month, "Mar") == 0 || strcmp(cars[i].lastTO.month, "Мар") == 0)
			month = 3;
		else if (strcmp(cars[i].lastTO.month, "Apr") == 0 || strcmp(cars[i].lastTO.month, "Апр") == 0)
			month = 4;
		else if (strcmp(cars[i].lastTO.month, "May") == 0 || strcmp(cars[i].lastTO.month, "Май") == 0)
			month = 5;
		else if (strcmp(cars[i].lastTO.month, "June") == 0 || strcmp(cars[i].lastTO.month, "Июнь") == 0)
			month = 6;
		else if (strcmp(cars[i].lastTO.month, "July") == 0 || strcmp(cars[i].lastTO.month, "Июль") == 0)
			month = 7;
		else if (strcmp(cars[i].lastTO.month, "Aug") == 0 || strcmp(cars[i].lastTO.month, "Авг") == 0)
			month = 8;
		else if (strcmp(cars[i].lastTO.month, "Sept") == 0 || strcmp(cars[i].lastTO.month, "Сен") == 0)
			month = 9;
		else if (strcmp(cars[i].lastTO.month, "Oct") == 0 || strcmp(cars[i].lastTO.month, "Окт") == 0)
			month = 10;
		else if (strcmp(cars[i].lastTO.month, "Nov") == 0 || strcmp(cars[i].lastTO.month, "Ноя") == 0)
			month = 11;
		else if (strcmp(cars[i].lastTO.month, "Dec") == 0 || strcmp(cars[i].lastTO.month, "Дек") == 0)
			month = 12;

		time = (double)(now->tm_year - year) * 12 + (now->tm_mon - month) + (double)(now->tm_mday - day) / 30.0;

		if (time > 18)
		{
			count++;
			tmpCar = (struct Car*)realloc(tmpCar, sizeof(struct Car) * count);
			tmpCar[count - 1] = cars[i];
		}
	}
	PrintTable(tmpCar, count);

	free(tmpCar);
}

void LoadFromFile(struct Car** cars, int* count)
{
	FILE* fin;
	int pos;
	char buff[26];
	if ((fin = fopen("base.txt", "r")) == NULL)
	{
		FILE* f = fopen("base.txt", "w");
		fclose(f);

		fin = fopen("base.txt", "r");
	}

	fseek(fin, 0, SEEK_END);
	pos = ftell(fin);
	if (pos > 0)
	{
		fseek(fin, 0, SEEK_SET);
		while (!feof(fin))
		{
			(*cars) = (struct Cars*)realloc((*cars), sizeof(struct Car) * (*count + 1));

			fscanf(fin, "%s", &buff);
			(*cars)[*count].brand = (char*)malloc((strlen(buff) + 1) * sizeof(char));
			strcpy((*cars)[*count].brand, buff);

			fscanf(fin, "%s", &buff);
			(*cars)[*count].owner.surname = (char*)malloc((strlen(buff) + 1) * sizeof(char));
			strcpy((*cars)[*count].owner.surname, buff);

			fscanf(fin, "%s", &buff);
			(*cars)[*count].owner.name = (char*)malloc((strlen(buff) + 1) * sizeof(char));
			strcpy((*cars)[*count].owner.name, buff);

			fscanf(fin, "%s", &buff);
			(*cars)[*count].owner.secondname = (char*)malloc((strlen(buff) + 1) * sizeof(char));
			strcpy((*cars)[*count].owner.secondname, buff);

			fscanf(fin, "%d", &(*cars)[*count].enginePower);
			fscanf(fin, "%d", &(*cars)[*count].mileage);
			fscanf(fin, "%d", &(*cars)[*count].lastTO.day);
			
			fscanf(fin, "%s", &buff);
			(*cars)[*count].lastTO.month = (char*)malloc((strlen(buff) + 1) * sizeof(char));
			strcpy((*cars)[*count].lastTO.month, buff);

			fscanf(fin, "%d", &(*cars)[*count].lastTO.year);
			(*count)++;
		}
	}
	fclose(fin);
}

void SaveToFile(struct Car* cars, int count)
{
	FILE* fout;
	if ((fout = fopen("base.txt", "w")) == NULL)
	{
		printf("Файл с таким именем не найден.\n");
		return;
	}
	for (int i = 0; i < count; i++)
	{
		fputs(cars[i].brand, fout);
		fputc('\t', fout);
		fputs(cars[i].owner.surname, fout);
		fputc('\t', fout);
		fputs(cars[i].owner.name, fout);
		fputc('\t', fout);
		fputs(cars[i].owner.secondname, fout);
		fputc('\t', fout);
		fprintf(fout, "%d\t", cars[i].enginePower);
		fprintf(fout, "%d\t", cars[i].mileage);
		fprintf(fout, "%d\t", cars[i].lastTO.day);
		fputs(cars[i].lastTO.month, fout);
		fputc('\t', fout);
		fprintf(fout, "%d", cars[i].lastTO.year);
		if (i != count - 1)
			fputc('\n', fout);
	}

	fclose(fout);
}

int main()
{
	setlocale(0, "russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	struct Car* cars = (struct Car*)malloc(0);
	int count = 0;
	LoadFromFile(&cars, &count);

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
		printf("5.Вывести машины, проходившие ТО более 18 месяцев назад\n");
		printf("6.Выход\n");
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
			FindByMileage(cars, count, intBuff);
			break;
		case 5:
			LastTOCar(cars, count);
			break;
		case 6:
			SaveToFile(cars, count);
			exit = 0;
		default:
			break;
		}
	}

	free(cars);
}