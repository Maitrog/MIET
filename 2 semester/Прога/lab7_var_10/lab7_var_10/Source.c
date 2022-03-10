#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <time.h>

struct Fio
{
	char* surname;
	char* name;
};

struct Date
{
	int day;
	char* month;
	int year;
};

struct Teacher
{
	struct Fio name;
	char* department;
	char* subject;
	struct Date technicalSecurity;
};

struct Teacher CreateTeacher()
{
	struct Teacher newTeacher;
	char buff[26];

	printf("Введите фамилию преподавателя: ");
	scanf("%25s", buff);
	newTeacher.name.surname = (char*)malloc((strlen(buff) + 1) * sizeof(char));
	strcpy(newTeacher.name.surname, buff);

	printf("Введите имя преподавателя: ");
	scanf("%25s", buff);
	newTeacher.name.name = (char*)malloc((strlen(buff) + 1) * sizeof(char));
	strcpy(newTeacher.name.name, buff);

	printf("Введите название кафедры (например ИПОВС,ВМ1,ПКИМС): ");
	scanf("%25s", buff);
	newTeacher.department = (char*)malloc((strlen(buff) + 1) * sizeof(char));
	strcpy(newTeacher.department, buff);

	printf("Введите предмет: ");
	scanf("%25s", buff);
	newTeacher.subject = (char*)malloc((strlen(buff) + 1) * sizeof(char));
	strcpy(newTeacher.subject, buff);

	printf("Введите дату последнего ИТБ\n");
	printf("День: ");
	scanf("%d", &newTeacher.technicalSecurity.day);

	printf("Месяц (Jan/Янв, Feb/Фев, Mar/Мар, Apr/Апр, May/Май, June/Июнь, July/Июль, Aug/Авг, Sept/Сен, Oct/Окт, Nov/Ноя, Dec/Дек): ");
	scanf("%25s", buff);
	newTeacher.technicalSecurity.month = (char*)malloc((strlen(buff) + 1) * sizeof(char));
	strcpy(newTeacher.technicalSecurity.month, buff);

	printf("Год: ");
	scanf("%d", &newTeacher.technicalSecurity.year);

	return newTeacher;
}

void PrintTable(struct Teacher* Teachers, int TeachersCount)
{
	if (TeachersCount > 0)
	{
		printf("%-26s%-26s%-26s%-26s%s", "Фамилия", "Имя", "Кафедра", "Предмет", "Дата последнего ИТБ\n");
		printf("--------------------------------------------------------------------------------------------------------------\n");
		for (int i = 0; i < TeachersCount; i++)
		{
			printf("%-26s%-26s%-26s%-26s%d %s %d\n", Teachers[i].name.surname, Teachers[i].name.name, Teachers[i].department, Teachers[i].subject, 
				Teachers[i].technicalSecurity.day, Teachers[i].technicalSecurity.month, Teachers[i].technicalSecurity.year);
		}
	}
}

struct Teacher* SortByName(struct Teacher* Teachers, int TeachersCount)
{
	for (int i = 0; i < TeachersCount - 1; i++)
		for (int j = 0; j < TeachersCount - 1; j++)
			if (strcmp(Teachers[j].name.surname, Teachers[j + 1].name.surname) == 1 || (strcmp(Teachers[j].name.surname, Teachers[j + 1].name.surname) == 0 && strcmp(Teachers[j].name.name, Teachers[j + 1].name.name) == 1))
			{
				struct Teacher tmp = Teachers[j];
				Teachers[j] = Teachers[j + 1];
				Teachers[j + 1] = tmp;
			}

	return Teachers;
}

void FindSubject(struct Teacher* teacher, int teacherCount, char* surname, char* name)
{
	int count = 0;
	for (int i = 0; i < teacherCount; i++)
		if (strcmp(teacher[i].name.name, name) == 0 && strcmp(teacher[i].name.surname, surname) == 0)
		{
			if (count == 0)
			{
				printf("Предметы: ");
				printf("%s", teacher[i].subject);
			}
			else
				printf(", %s", teacher[i].subject);
			count++;
		}
}

void FindByDepartment(struct Teacher* teacher, int teacherCount, char* dep)
{
	struct Teacher* depTeacher = (struct Teacher*)malloc(0);
	int count = 0;

	for (int i = 0; i < teacherCount; i++)
		if (strcmp(teacher[i].department, dep) == 0)
		{
			count++;
			depTeacher = (struct Teacher*)realloc(depTeacher, sizeof(struct Teacher) * count);
			depTeacher[count - 1] = teacher[i];
		}

	depTeacher = SortByName(depTeacher, count);
	PrintTable(depTeacher, count);
}

void LastTSTeacher(struct Teacher* teachers, int teachersCount)
{
	time_t t = time(0);
	struct tm* now = localtime(&t);
	double time = 0.0;
	struct Teacher* tmpTeacher = (struct Teacher*)malloc(0);
	int count = 0;
	
	for (int i = 0; i < teachersCount; i++)
	{
		int day = teachers[i].technicalSecurity.day;
		int month = -1;
		int year = teachers[i].technicalSecurity.year;
		if (strcmp(teachers[i].technicalSecurity.month, "Jan") == 0 || strcmp(teachers[i].technicalSecurity.month, "Янв") == 0)
			month = 1;
		else if (strcmp(teachers[i].technicalSecurity.month, "Feb") == 0 || strcmp(teachers[i].technicalSecurity.month, "Фев") == 0)
			month = 2;
		else if (strcmp(teachers[i].technicalSecurity.month, "Mar") == 0 || strcmp(teachers[i].technicalSecurity.month, "Мар") == 0)
			month = 3;
		else if (strcmp(teachers[i].technicalSecurity.month, "Apr") == 0 || strcmp(teachers[i].technicalSecurity.month, "Апр") == 0)
			month = 4;
		else if (strcmp(teachers[i].technicalSecurity.month, "May") == 0 || strcmp(teachers[i].technicalSecurity.month, "Май") == 0)
			month = 5;
		else if (strcmp(teachers[i].technicalSecurity.month, "June") == 0 || strcmp(teachers[i].technicalSecurity.month, "Июнь") == 0)
			month = 6;
		else if (strcmp(teachers[i].technicalSecurity.month, "July") == 0 || strcmp(teachers[i].technicalSecurity.month, "Июль") == 0)
			month = 7;
		else if (strcmp(teachers[i].technicalSecurity.month, "Aug") == 0 || strcmp(teachers[i].technicalSecurity.month, "Авг") == 0)
			month = 8;
		else if (strcmp(teachers[i].technicalSecurity.month, "Sept") == 0 || strcmp(teachers[i].technicalSecurity.month, "Сен") == 0)
			month = 9;
		else if (strcmp(teachers[i].technicalSecurity.month, "Oct") == 0 || strcmp(teachers[i].technicalSecurity.month, "Окт") == 0)
			month = 10;
		else if (strcmp(teachers[i].technicalSecurity.month, "Nov") == 0 || strcmp(teachers[i].technicalSecurity.month, "Ноя") == 0)
			month = 11;
		else if (strcmp(teachers[i].technicalSecurity.month, "Dec") == 0 || strcmp(teachers[i].technicalSecurity.month, "Дек") == 0)
			month = 12;

		time = (double)(now->tm_year + 1900 - year) * 12 + (now->tm_mon + 1 - month) + (double)(now->tm_mday - day) / 30.0;

		if (time > 15)
		{
			count++;
			tmpTeacher = (struct Teacher*)realloc(tmpTeacher, sizeof(struct Teacher) * count);
			tmpTeacher[count - 1] = teachers[i];
		}
	}
	PrintTable(tmpTeacher, count);

	free(tmpTeacher);
}

void LoadFromFile(struct Teacher** teachers, int* count)
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
			(*teachers) = (struct Teachers*)realloc((*teachers), sizeof(struct Teacher) * (*count + 1));

			fscanf(fin, "%25s", &buff);
			(*teachers)[*count].name.surname = (char*)malloc((strlen(buff) + 1) * sizeof(char));
			strcpy((*teachers)[*count].name.surname, buff);

			fscanf(fin, "%25s", &buff);
			(*teachers)[*count].name.name = (char*)malloc((strlen(buff) + 1) * sizeof(char));
			strcpy((*teachers)[*count].name.name, buff);

			fscanf(fin, "%25s", &buff);
			(*teachers)[*count].department = (char*)malloc((strlen(buff) + 1) * sizeof(char));
			strcpy((*teachers)[*count].department, buff);

			fscanf(fin, "%25s", &buff);
			(*teachers)[*count].subject = (char*)malloc((strlen(buff) + 1) * sizeof(char));
			strcpy((*teachers)[*count].subject, buff);

			fscanf(fin, "%d", &(*teachers)[*count].technicalSecurity.day);

			fscanf(fin, "%25s", &buff);
			(*teachers)[*count].technicalSecurity.month = (char*)malloc((strlen(buff) + 1) * sizeof(char));
			strcpy((*teachers)[*count].technicalSecurity.month, buff);

			fscanf(fin, "%d", &(*teachers)[*count].technicalSecurity.year);
			(*count)++;
		}
	}
	fclose(fin);
}

void SaveToFile(struct Teacher* teachers, int count)
{
	FILE* fout;
	if ((fout = fopen("base.txt", "w")) == NULL)
	{
		printf("Файл с таким именем не найден.\n");
		return;
	}
	for (int i = 0; i < count; i++)
	{
		fputs(teachers[i].name.surname, fout);
		fputc('\t', fout);
		fputs(teachers[i].name.name, fout);
		fputc('\t', fout);
		fputs(teachers[i].department, fout);
		fputc('\t', fout);
		fputs(teachers[i].subject, fout);
		fputc('\t', fout);
		fprintf(fout, "%d\t", teachers[i].technicalSecurity.day);
		fputs(teachers[i].technicalSecurity.month, fout);
		fputc('\t', fout);
		fprintf(fout, "%d", teachers[i].technicalSecurity.year);
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

	struct Teacher* Teachers = (struct Teacher*)malloc(0);
	int count = 0;
	LoadFromFile(&Teachers, &count);
	char buff[51];
	char buff2[51];
	int c;
	int exit = 1;
	while (exit)
	{
		printf("1.Добавить преподавателя\n");
		printf("2.Распечатать информацию о преподавателях\n");
		printf("3.Найти все предметы, которые ведёт преподаватель\n");
		printf("4.Найти всех преподавателей заданной кафедры\n");
		printf("5.Найти преподавателей, у которых с последнего ИТБ прошло больше 15 месяцев\n");
		printf("6.Выход\n");
		printf("Введите команду: ");

		scanf("%d", &c);

		switch (c)
		{
		case 1:
			count++;
			Teachers = (struct Teacher*)realloc(Teachers, sizeof(struct Teacher) * count);
			Teachers[count - 1] = CreateTeacher();
			break;
		case 2:
			PrintTable(Teachers, count);
			break;
		case 3:
			printf("\nВведите фамилию преподавателя: ");
			scanf("%s50", buff);
			printf("\nВведите имя преподавателя: ");
			scanf("%s50", buff2);
			FindSubject(Teachers, count, buff, buff2);
			break;
		case 4:
			printf("\nВведите название кафедры: ");
			scanf("%s50", &buff);
			FindByDepartment(Teachers, count, buff);
			break;
		case 5:
			LastTSTeacher(Teachers, count);
			break;
		case 6:
			SaveToFile(Teachers, count);
			exit = 0;
		default:
			break;
		}
	}

	free(Teachers);
}