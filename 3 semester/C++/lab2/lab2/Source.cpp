#include <iostream>
#include "Student.h"
#include <iterator>
#include <fstream>
#include <Windows.h>

void show_table(Student*);

void find_student(Student*);


int main()
{
	setlocale(0, "russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::fstream file("base.txt", std::ios::app);
	file.close();

	std::ifstream fin("base.txt");
	Student* student_base  = new Student[0];
	Student* tmp;
	std::string _name;
	std::string _lastname;
	std::string _faculty;
	int _group;

	if (!fin)
	{
		std::cout << "Ошибка открытия файла.\n";
		return -1;
	}

	while (fin >> _lastname)
	{
		fin >> _name;
		fin >> _faculty;
		fin >> _group;
		tmp = new Student[Student::count + 1];
		for (size_t i = 0; i < (Student::count - 1) / 2; ++i)
		{
			tmp[i] = student_base[i];
		}
		delete[] student_base;
		student_base = tmp;
		student_base[Student::count - 2] = (Student(_lastname, _name, _faculty, _group));
	}
	fin.close();
	
	std::ofstream fout("base.txt");
	int k;
	for (;;)
	{
		std::cout << "1.Добавить студента." << std::endl;
		std::cout << "2.Вывести таблицу на экран." << std::endl;
		std::cout << "3.Найти студента по фамилии." << std::endl;
		std::cout << "4.Найти студента по номеру группы." << std::endl;
		std::cout << "5.Сортировать по алфавиту." << std::endl;
		std::cout << "6.Выход." << std::endl;
		while (true)
		{
			std::cout << "Введите команду: ";
			std::cin >> k;
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(32768, '\n');
				std::cout << "Ошибка ввода!\n";
			}
			else
				break;
		}
		switch (k)
		{
		case 1:
			std::cout << "Введите фамилии студента: ";
			std::cin >> _lastname;
			std::cout << "Введите имя студента: ";
			std::cin >> _name;
			std::cout << "Введите название факультета: ";
			std::cin >> _faculty;

			while (true)
			{
				std::cout << "Введите номер группы: ";
				std::cin >> _group;
				if (std::cin.fail())
				{
					std::cin.clear();
					std::cin.ignore(32768, '\n');
					std::cout << "Ошибка ввода!\n";
				}
				else
					break;
			}
			tmp = new Student[Student::count + 1];
			for (int i = 0; i < (Student::count - 1) / 2; ++i)
			{
				tmp[i] = student_base[i];
			}
			delete[] student_base;
			student_base = tmp;
			student_base[Student::count - 2] = (Student(_lastname, _name, _faculty, _group));
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
			delete[] student_base;
			return 0;
			break;
		default:
			std::cout << "Такой команды не существует.\n";
			break;
		}
	}
	return 0;
}

void show_table(Student* student_base)
{
	std::cout.setf(std::ios::left);
	std::cout.width(30);
	std::cout << "Фамилия";
	std::cout.width(30);
	std::cout << "Имя";
	std::cout.width(30);
	std::cout << "Факультет";
	std::cout.width(5);
	std::cout << "Группа\n";

	for (size_t i = 0; i<Student::count;++i)
	{
		std::cout << student_base[i];
	}
}

void find_student(Student* student_base)
{
	std::string last_name;

	std::cout << "Введите фамилию студента: ";
	std::cin >> last_name;

	size_t i;
	for (i = 0; i < Student::count; ++i)
	{
		if ((student_base[i]).is_fam(last_name))
		{
			std::cout.setf(std::ios::left);
			std::cout.width(30);
			std::cout << "Фамилия";
			std::cout.width(30);
			std::cout << "Имя";
			std::cout.width(30);
			std::cout << "Факультет";
			std::cout.width(5);
			std::cout << "Группа\n";
			std::cout << (student_base[i]);
			break;
		}
	}

	if (i == Student::count)
		std::cout << "Студент не найден.\n";
}