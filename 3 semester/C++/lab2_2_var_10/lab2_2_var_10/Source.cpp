#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include "Teacher.h"

int isalphastr(std::string, int);

int main()
{
	setlocale(0, "russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::fstream file("base.txt", std::ios::app);
	file.close();

	std::ifstream fin("base.txt");
	Teacher* teacher_base = new Teacher[0];
	std::string fullName = "";
	Name name;
	std::string buff;
	int status;
	int department;		
	int c;				//выбор команды
	bool flag = false;	//флаг отвечающий за то, найден ли преподаватель по эталонному объекту


	if (!fin)
	{
		std::cout << "Ошибка открытия файла.\n";
		return -1;
	}

	while (fin >> department)
	{
		fin >> buff;
		fullName += buff;
		while (true, fin >> buff)
		{
			if (atoi(buff.c_str()) > 0)
				break;
			else
			{
				fullName += " " + buff ;
			}
		}
		status = atoi(buff.c_str());

		teacher_base = Teacher::add_teacher(teacher_base, Teacher(department, Name(fullName), status));
		fullName = "";
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
		std::cout << "6.Find reference object" << std::endl;
		std::cout << "7.Exit" << std::endl;
		std::cin >> c;
		switch (c)
		{
		case 1:
			std::cin.clear();
			std::cin.ignore(32768, '\n');
			std::cin >> name;

			do
			{
				std::cout << "Enter teacher's department: 1-IPOVS, 2-VM, 3-VT: ";
				std::cin >> department;
				if (std::cin.fail())
				{
					std::cin.clear();
					std::cin.ignore(32768, '\n');
				}
			} while (department != 1 && department != 2 && department != 3);

			do
			{
				std::cout << "Enter teacher's status (1-Teacher, 2-Docent, 3-Doctor of since): ";
				std::cin >> status;
				if (std::cin.fail())
				{
					std::cin.clear();
					std::cin.ignore(32768, '\n');
				}
			} while (status != 1 && status != 2 && status != 3);

			teacher_base = Teacher::add_teacher(teacher_base, Teacher(department, name, status));
			break;
		case 2:
			Teacher::show_table(teacher_base, Teacher::count);
			break;
		case 3:
			std::cin.clear();
			std::cin.ignore(32768, '\n');
			std::cin >> name;

			Teacher::find_by_full_name(teacher_base, name);
			break;
		case 4:
			do
			{
				std::cout << "Enter teacher's status (1-Teacher, 2-Docent, 3-Doctor of since): ";
				std::cin >> status;
				if (std::cin.fail())
				{
					std::cin.clear();
					std::cin.ignore(32768, '\n');
				}
			} while (status != 1 && status != 2 && status != 3);
			find_by_status(teacher_base, status);
			break;
		case 5:
			sort_by_full_name(teacher_base, Teacher::count);
			break;
		case 6:
			std::cin.clear();
			std::cin.ignore(32768, '\n');
			std::cin >> name;

			do
			{
				std::cout << "Enter teacher's department: 1-IPOVS, 2-VM, 3-VT: ";
				std::cin >> department;
				if (std::cin.fail())
				{
					std::cin.clear();
					std::cin.ignore(32768, '\n');
				}
			} while (department != 1 && department != 2 && department != 3);

			do
			{
				std::cout << "Enter teacher's status (1-Teacher, 2-Docent, 3-Doctor of since): ";
				std::cin >> status;
				if (std::cin.fail())
				{
					std::cin.clear();
					std::cin.ignore(32768, '\n');
				}
			} while (status != 1 && status != 2 && status != 3);

			flag = false;

			for (int i = 0; i < Teacher::count; i++)
			{
				if (teacher_base[i] == Teacher(department, name, status))
				{
					std::cout << "Teacher found." << std::endl;
					flag = true;
				}
			}
			if (!flag)
			{
				std::cout << "Teacher not found." << std::endl;
				std::cout << "It will be added to the list." << std::endl;
				Teacher::add_teacher(teacher_base, Teacher(department, name, status));
			}
			break;
		case 7:
			for (size_t i = 0; i < Teacher::count; i++)
			{
				fout << teacher_base[i].get_department() << " " << teacher_base[i].get_fullName() << " " << teacher_base[i].get_status() << std::endl;
			}
			delete[] teacher_base;
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

int isalphastr(std::string str, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (!(isalpha(str[i]) || str[i] == ' ' || str[i] >= 'а' && str[i] <= 'я' || str[i] >= 'А' && str[i] <= 'Я' || str[i] == 'ё' || str[i] == 'Ё'))
			return 0;
	}
	return 1;
}