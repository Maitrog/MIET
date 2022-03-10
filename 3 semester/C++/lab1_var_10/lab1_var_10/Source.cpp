#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <Windows.h>
struct Teacher
{
	int department;
	char* fullName;
	int status;
	static int count;
};

int Teacher::count = 0;

struct Teacher* add_teacher(struct Teacher*);

void show_table(struct Teacher*, int);

void find_by_full_name(struct Teacher*);

void find_by_status(struct Teacher*);

void sort_by_full_name(struct Teacher*);

int isalphastr(char*, int);



int main()
{
	setlocale(0, "russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::fstream file("base.txt", std::ios::app);
	file.close();

	std::ifstream fin("base.txt");
	struct Teacher* teacher_base;
	teacher_base = (struct Teacher*)malloc(sizeof(struct Teacher));
	int k;
	char buff[50];

	if (!fin)
	{
		std::cout << "File cann't be open!\n";
		return -1;
	}

	while (teacher_base = (struct Teacher*)realloc(teacher_base, (Teacher::count + 1) * sizeof(struct Teacher)), fin >> buff)
	{
		teacher_base[Teacher::count].department = atoi(buff);
		fin >> buff;
		teacher_base[Teacher::count].fullName = (char*)malloc(50 * sizeof(char));
		strcpy(teacher_base[Teacher::count].fullName, buff);
		while (true, fin >> buff)
		{
			if (atoi(buff) > 0)
				break;
			else
			{
				teacher_base[Teacher::count].fullName = strcat(teacher_base[Teacher::count].fullName, " ");
				teacher_base[Teacher::count].fullName = strcat(teacher_base[Teacher::count].fullName, buff);
			}
		}
		teacher_base[Teacher::count].status = atoi(buff);
		Teacher::count++;
	}
	fin.close();

	std::ofstream fout("base.txt");
	for (;;)
	{
		std::cout << "1.Add teacher" << std::endl;
		std::cout << "2.Show table" << std::endl;
		std::cout << "3.Find teacher by full name" << std::endl;
		std::cout << "4.Find teacher by status" << std::endl;
		std::cout << "5.Sort by full name" << std::endl;
		std::cout << "6.Exit" << std::endl;
		std::cin >> k;
		switch (k)
		{
		case 1:
			teacher_base = add_teacher(teacher_base);
			break;
		case 2:
			show_table(teacher_base, Teacher::count);
			break;
		case 3:
			find_by_full_name(teacher_base);
			break;
		case 4:
			find_by_status(teacher_base);
			break;
		case 5:
			sort_by_full_name(teacher_base);
			break;
		case 6:
			for (size_t i = 0; i < Teacher::count; i++)
			{
				fout << teacher_base[i].department << " " << teacher_base[i].fullName << " " << teacher_base[i].status << std::endl;
			}
			free(teacher_base);
			fout.close();
			return 0;
			break;
		default:
			std::cin.clear();
			std::cin.ignore(32768, '\n');
			std::cout << "Command is not found.\n";
			break;
		}
	}

	return 0;
}

struct Teacher* add_teacher(struct Teacher* teacher_base)
{
	teacher_base = (struct Teacher*)realloc(teacher_base, (Teacher::count + 1) * sizeof(struct Teacher));
	char buff[50];
	std::cin.clear();
	std::cin.ignore(32768, '\n');

	do
	{
		std::cout << "Enter teacher's full name: ";
		fgets(buff, 49, stdin);
	} while (!isalphastr(buff, strlen(buff)));
	buff[strlen(buff) - 1] = NULL;
	teacher_base[Teacher::count].fullName = (char*)malloc(strlen(buff) * sizeof(char));
	strcpy(teacher_base[Teacher::count].fullName, buff);

	do
	{
		std::cout << "Enter teacher's department: 1-IPOVS, 2-VM, 3-VT: ";
		std::cin >> teacher_base[Teacher::count].department;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(32768, '\n');
		}
	} while (teacher_base[Teacher::count].department != 1 && teacher_base[Teacher::count].department != 2 && teacher_base[Teacher::count].department != 3);
	
	do
	{
		std::cout << "Enter teacher's status (1-Teacher, 2-Docent, 3-Doctor of since): ";
		std::cin >> teacher_base[Teacher::count].status;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(32768, '\n');
		}
	} while (teacher_base[Teacher::count].status != 1 && teacher_base[Teacher::count].status != 2 && teacher_base[Teacher::count].status != 3);

	Teacher::count++;
	return teacher_base;
}

void show_table(struct Teacher* teacher_base, int size)
{
	std::cout << std::endl;
	std::cout.setf(std::ios::left);
	std::cout.width(11);
	std::cout << "Department";
	std::cout.width(51);
	std::cout << "Full name";
	std::cout.width(16);
	std::cout << "Status" << std::endl;

	for (int i = 0; i < size; i++)
	{
		std::cout.setf(std::ios::left);
		std::cout.width(11);
		switch (teacher_base[i].department)
		{
		case 1:
			std::cout << "IPOVS";
			break;
		case 2:
			std::cout << "VM";
			break;
		case 3:
			std::cout << "VT";
			break;
		default:
			break;
		}
		std::cout.width(51);
		std::cout << teacher_base[i].fullName;
		std::cout.width(16);
		switch (teacher_base[i].status)
		{
		case 1:
			std::cout << "Teacher" << std::endl;
			break;
		case 2:
			std::cout << "Docent" << std::endl;
			break;
		case 3:
			std::cout << "Doctor of since" << std::endl;
			break;
		default:
			break;
		}
	}
	std::cout << std::endl;
}

void find_by_full_name(struct Teacher* teacher_base)
{
	char str[50];
	struct Teacher* tmp = (struct Teacher*)malloc(sizeof(struct Teacher));
	int new_count = 0;
	std::cout << "Enter teacher's full name: ";
	std::cin >> str;
	for (size_t i = 0; i < Teacher::count; ++i)
	{
		if (!strcmp(str, teacher_base[i].fullName))
		{
			tmp = (struct Teacher*)realloc(tmp, (new_count + 1) * sizeof(struct Teacher));
			tmp[new_count] = teacher_base[i];
			new_count++;
		}
	}
	if (!new_count)
	{
		std::cout << "Teacher not found.\n";
	}
	else
	{
		show_table(tmp, new_count);
	}
	free(tmp);
}

void find_by_status(struct Teacher* teacher_base)
{
	int status;
	struct Teacher* tmp = (struct Teacher*)malloc(sizeof(struct Teacher));
	int new_count = 0;
	std::cout << "Enter teacher's status (1-Teacher, 2-Docent, 3-Doctor of since): ";
	std::cin >> status;
	for (size_t i = 0; i < Teacher::count; ++i)
	{
		if (status == teacher_base[i].status)
		{
			tmp = (struct Teacher*)realloc(tmp, (new_count + 1) * sizeof(struct Teacher));
			tmp[new_count] = teacher_base[i];
			new_count++;
		}
	}
	if (!new_count)
	{
		std::cout << "\nTeacher not found.\n";
	}
	else
	{
		show_table(tmp, new_count);
	}
	free(tmp);
}

void sort_by_full_name(struct Teacher* teacher_base)
{
	int size = Teacher::count;
	for (int step = size / 2; step > 0; step /= 2)
	{
		for (int i = step; i < size; ++i)
		{
			for (int j = i - step; j >= 0 && (strcmp(teacher_base[j].fullName, teacher_base[j + step].fullName) == 1); j -= step)
			{
				struct Teacher tmp = teacher_base[j];
				teacher_base[j] = teacher_base[j + step];
				teacher_base[j + step] = tmp;
			}

		}
	}
	show_table(teacher_base, Teacher::count);
}

int isalphastr(char* str,int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		if (!(isalpha(str[i]) || str[i] == ' ' || str[i]>='à' && str[i] <= 'ÿ' || str[i] >= 'À' && str[i] <= 'ß' || str[i] == '¸' || str[i] == '¨'))
			return 0;
	}
	return 1;
}