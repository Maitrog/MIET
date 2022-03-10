#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <Windows.h>

struct Teacher
{
	char* surname;
	char* name;
	char* department;
	char* subject;
};

struct Teacher CreateTeacher()
{
	struct Teacher newTeacher;
	char buff[26];

	printf("Введите фамилию преподавателя: ");
	scanf("%25s", buff);
	newTeacher.surname = (char*)malloc((strlen(buff) + 1) * sizeof(char));
	strcpy(newTeacher.surname, buff);

	printf("Введите имя преподавателя: ");
	scanf("%25s", buff);
	newTeacher.name = (char*)malloc((strlen(buff) + 1) * sizeof(char));
	strcpy(newTeacher.name, buff);

	printf("Введите название кафедры (например ИПОВС,ВМ1,ПКИМС): ");
	scanf("%25s", buff);
	newTeacher.department = (char*)malloc((strlen(buff) + 1) * sizeof(char));
	strcpy(newTeacher.department, buff);

	printf("Введите предмет: ");
	scanf("%25s", buff);
	newTeacher.subject = (char*)malloc((strlen(buff) + 1) * sizeof(char));
	strcpy(newTeacher.subject, buff);

	return newTeacher;
}

void PrintTable(struct Teacher* Teachers, int TeachersCount)
{
	if (TeachersCount > 0)
	{
		printf("%-26s%-26s%-26s%s", "Фамилия", "Имя", "Кафедра", "Предмет\n");
		printf("--------------------------------------------------------------------------------------------------------------\n");
		for (int i = 0; i < TeachersCount; i++)
		{
			printf("%-26s%-26s%-26s%s\n", Teachers[i].surname, Teachers[i].name, Teachers[i].department, Teachers[i].subject);
		}
	}
}

struct Teacher* SortByName(struct Teacher* Teachers, int TeachersCount)
{
	for (int i = 0; i < TeachersCount - 1; i++)
		for (int j = 0; j < TeachersCount - 1; j++)
			if (strcmp(Teachers[j].surname, Teachers[j + 1].surname) == 1 || (strcmp(Teachers[j].surname, Teachers[j + 1].surname) == 0 && strcmp(Teachers[j].name, Teachers[j + 1].name) == 1))
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
		for(int i = 0; i < teacherCount; i++)
			if (strcmp(teacher[i].name, name)==0 && strcmp(teacher[i].surname, surname)==0)
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

	for(int i = 0; i<teacherCount; i++)
		if (strcmp(teacher[i].department, dep)==0)
		{
			count++;
			depTeacher = (struct Teacher*)realloc(depTeacher, sizeof(struct Teacher) * count);
			depTeacher[count - 1] = teacher[i];
		}

	depTeacher = SortByName(depTeacher, count);
	PrintTable(depTeacher, count);
}

int main()
{
	setlocale(0, "russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	struct Teacher* Teachers = (struct Teacher*)malloc(0);
	int count = 0;
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
		printf("5.Выход\n");
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
			exit = 0;
		default:
			break;
		}
	}

	free(Teachers);
}