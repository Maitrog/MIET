#include "Student.h"
#include <iostream>
#include <fstream>

int Student::count = 0;

std::ostream& operator<<(std::ostream& out, const Student& stud)
{
	std::cout.setf(std::ios::left);
	out.width(30);
	out << stud.fam;
	out.width(30);
	out << stud.name;
	out.width(30);
	out << stud.faculty;
	out.width(5);
	out << stud.grup;
	out << std::endl;
	return out;
}

bool Student::is_fam(std::string str)
{
	return str == fam;
}

void find_by_group_number(Student* student_base)
{
	int grup;
	int count = 0;

	std::cout << "Введите номер группы: ";
	std::cin >> grup;

	for (size_t i = 0; i < Student::count; ++i)
	{
		if (grup == (student_base[i]).grup)
		{
			if (!count)
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
			}
			std::cout << (student_base[i]);
			++count;
		}
	}
	if (!count)
		std::cout << "Студент не найден.\n";

}

void show_table(Student* student_base);

//Shell sort
void sort_by_name(Student* student_base)
{
	int size = Student::count;
	for (int step = size / 2; step > 0; step /= 2)
	{
		for (int i = step; i < size; ++i)
		{
			for (int j = i - step; j >= 0 && (student_base[j].fam > student_base[j + step].fam ||
				(student_base[j].fam == student_base[j + step].fam && student_base[j].name > student_base[j + step].name)); j -= step)
			{
				Student tmp = student_base[j];
				student_base[j] = student_base[j + step];
				student_base[j + step] = tmp;
			}

		}
	}
	show_table(student_base);
}