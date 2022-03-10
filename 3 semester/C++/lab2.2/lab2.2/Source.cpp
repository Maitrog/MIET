#include <iostream>
#include "Student.h"
#include <iterator>
#include <fstream>


void show_table(Student*);

void find_student(Student*);


int main()
{
	std::ifstream fin("base.txt");
	Student* student_base = new Student[25];
	std::string _name;
	std::string _lastname;
	std::string _faculty;
	int _group;

	if (!fin)
	{
		std::cout << "File is not found.\n";
		return -1;
	}

	while (fin >> _lastname)
	{
		fin >> _name;
		fin >> _faculty;
		fin >> _group;
		student_base[Student::count - 1] = (Student(_lastname, _name, _faculty, _group));
	}
	fin.close();

	std::ofstream fout("base.txt");
	int k;
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
			std::cout << "Enter student's last name: ";
			std::cin >> _lastname;
			std::cout << "Enter student's name: ";
			std::cin >> _name;
			std::cout << "Enter student's faculty: ";
			std::cin >> _faculty;
			std::cout << "Enter student's group: ";
			std::cin >> _group;
			student_base[Student::count - 1] = (Student(_lastname, _name, _faculty, _group));
			break;
		case 2:
			show_table(student_base);
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
			for (size_t i = 0; i < Student::count; ++i)
			{
				fout << student_base[i];
			}
			fout.close();
			return 0;
			break;
		default:
			std::cout << "Command is not found.\n";
			break;
		}
	}
	delete[] student_base;
	return 0;
}

void show_table(Student* student_base)
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

	for (size_t i = 0; i < Student::count; ++i)
	{
		std::cout << student_base[i];
	}
}

void find_student(Student* student_base)
{
	std::string last_name;

	std::cout << "Enter student's last name: ";
	std::cin >> last_name;

	size_t i;
	for (i = 0; i < Student::count; ++i)
	{
		if ((student_base[i]).is_last_name(last_name))
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
			std::cout << (student_base[i]);
			break;
		}
	}

	if (i == Student::count)
		std::cout << "Student is not found.\n";
}