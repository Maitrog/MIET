#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>

static int count;

struct Student
{
	char* name;
	char* fam;
	char* faculty;
	int grup;
};

struct Student* add_student(struct Student*);

void show_table(struct Student*, int);

void find_student(struct Student*);

void find_by_group_number(struct Student*);

void sort_by_name(struct Student*);

int main()
{
	std::fstream file("base.txt", std::ios::app);
	file.close();

	std::ifstream fin("base.txt");
	struct Student* student_base;
	student_base = (struct Student*)malloc(sizeof(struct Student));
	int k;
	char buff[30];
	count = 0;

	if (!fin)
	{
		std::cout << "Error!\n";
		return -1;
	}

	while (student_base = (struct Student*)realloc(student_base, (count + 1) * sizeof(struct Student)), fin >> buff)
	{
		student_base[count].fam = (char*)malloc(strlen(buff) * sizeof(char));
		strcpy(student_base[count].fam, buff);
		fin >> buff;
		student_base[count].name = (char*)malloc(strlen(buff) * sizeof(char));
		strcpy(student_base[count].name, buff);
		fin >> buff;
		student_base[count].faculty = (char*)malloc(strlen(buff) * sizeof(char));
		strcpy(student_base[count].faculty, buff);
		fin >> student_base[count].grup;
		count++;
	}
	fin.close();

	std::ofstream fout("base.txt");
	for (;;)
	{
		std::cout << "1.Add student" << std::endl;
		std::cout << "2.Show table" << std::endl;
		std::cout << "3.Find student" << std::endl;
		std::cout << "4.Find by group number" << std::endl;
		std::cout << "5.Sort by name" << std::endl;
		std::cout << "6.Exit" << std::endl;
		std::cin >> k;
		switch (k)
		{
		case 1:
			student_base = add_student(student_base);
			break;
		case 2:
			show_table(student_base, count);
			break;
		case 3:
			find_student(student_base);
			break;
		case 4:
			find_by_group_number(student_base);
			break;
		case 5:
			sort_by_name(student_base);
			break;
		case 6:
			for (size_t i = 0; i < count; i++)
			{
				fout << student_base[i].fam << " " << student_base[i].name << " " << student_base[i].faculty << " " << student_base[i].grup << std::endl;
			}
			free(student_base);
			fout.close();
			return 0;
			break;
		default:
			std::cout << "Command is not found.\n";
			break;
		}
	}
		return 0;
}
struct Student* add_student(struct Student* student_base)
{
	student_base = (struct Student*)realloc(student_base, (count + 1) * sizeof(struct Student));
	char buff[30];
	std::cout << "Enter student's last name: ";
	std::cin >> buff;
	student_base[count].fam = (char*)malloc(strlen(buff) * sizeof(char));
	strcpy(student_base[count].fam, buff);
	std::cout << "Enter student's name: ";
	std::cin >> buff;
	student_base[count].name = (char*)malloc(strlen(buff) * sizeof(char));
	strcpy(student_base[count].name, buff);
	std::cout << "Enter student's faculty: ";
	std::cin >> buff;
	student_base[count].faculty = (char*)malloc(strlen(buff) * sizeof(char));
	strcpy(student_base[count].faculty, buff);
	std::cout << "Enter student's group: ";
	std::cin >> student_base[count].grup;
	count++;
	return student_base;
}

void show_table(struct Student* student_base, int size_table)
{
	std::cout.setf(std::ios::left);
	std::cout.width(30);
	std::cout << "Last name";
	std::cout.width(30);
	std::cout << "Name";
	std::cout.width(30);
	std::cout << "Faculti";
	std::cout.width(5);
	std::cout << "Group\n";

	for (size_t i = 0; i < count; ++i)
	{
		std::cout.setf(std::ios::left);
		std::cout.width(30);
		std::cout << student_base[i].fam;
		std::cout.width(30);
		std::cout << student_base[i].name;
		std::cout.width(30);
		std::cout << student_base[i].faculty;
		std::cout.width(5);
		std::cout << student_base[i].grup << std::endl;
	}
}

void find_student(struct Student* student_base)
{
	char str[30];
	struct Student* tmp = (struct Student*)malloc(sizeof(struct Student));
	int new_count = 0;
	std::cout << "Enter student's group: ";
	std::cin >> str;
	for (size_t i = 0; i < count; ++i)
	{
		if (!strcmp(str, student_base[i].fam))
		{
			tmp = (struct Student*)realloc(tmp, (new_count + 1) * sizeof(struct Student));
			tmp[new_count] = student_base[i];
			new_count++;
		}
	}
	if (!new_count) 
	{ 
		std::cout << "Student not found.\n";
	}
	else
	{
		show_table(tmp, new_count);
	}
	free(tmp);
}

void find_by_group_number(struct Student* student_base)
{
	int group;
	struct Student* tmp = (struct Student*)malloc(sizeof(struct Student));
	int new_count = 0;
	std::cout << "Enter student's lastname: ";
	std::cin >> group;
	for (size_t i = 0; i < count; ++i)
	{
		if (group == student_base[i].grup)
		{
			tmp = (struct Student*)realloc(tmp, (new_count + 1) * sizeof(struct Student));
			tmp[new_count] = student_base[i];
			new_count++;
		}
	}
	if (!new_count)
	{
		std::cout << "Student not found.\n";
	}
	else
	{
		show_table(tmp, new_count);
	}
	free(tmp);
}

void sort_by_name(struct Student* student_base)
{
	int size = count;
	for (int step = size / 2; step > 0; step /= 2)
	{
		for (int i = step; i < size; ++i)
		{
			for (int j = i - step; j >= 0 && (strcmp(student_base[j].fam, student_base[j + step].fam) == 1 ||
				(!strcmp(student_base[j].fam, student_base[j + step].fam) && strcmp(student_base[j].name, student_base[j + step].name) == 1)); j -= step)
			{
				struct Student tmp = student_base[j];
				student_base[j] = student_base[j + step];
				student_base[j + step] = tmp;
			}

		}
	}
	show_table(student_base, count);
}