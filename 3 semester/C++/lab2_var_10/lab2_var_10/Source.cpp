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
	std::string buff;
	int status;
	int department;
	int k;

	if (!fin)
	{
		std::cout << "������ �������� �����.\n";
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

		teacher_base = Teacher::add_teacher(teacher_base, Teacher(department, fullName, status));
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
		std::cout << "6.Exit" << std::endl;
		std::cin >> k;
		switch (k)
		{
		case 1:
			do
			{
				std::cout << "Enter teacher's full name: ";
				std::cin.clear();
				std::cin.ignore(32768, '\n');
				std::getline(std::cin, fullName);
			} while (!isalphastr(fullName, fullName.length()));

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

			teacher_base = Teacher::add_teacher(teacher_base, Teacher(department, fullName, status));
			break;
		case 2:
			Teacher::show_table(teacher_base, Teacher::count);
			break;
		case 3:
			do
			{
				std::cout << "Enter teacher's full name: ";
				std::cin.clear();
				std::cin.ignore(32768, '\n');
				std::getline(std::cin, fullName);
			} while (!isalphastr(fullName, fullName.length()));

			Teacher::find_by_full_name(teacher_base, fullName);
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
		if (!(isalpha(str[i]) || str[i] == ' ' || str[i] >= '�' && str[i] <= '�' || str[i] >= '�' && str[i] <= '�' || str[i] == '�' || str[i] == '�'))
			return 0;
	}
	return 1;
}