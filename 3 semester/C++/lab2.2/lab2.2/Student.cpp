#include "Student.h"
#include <iostream>
#include <fstream>

int Student::count = 0;

Student::Student() :faculty(""), grup(0)
{
	man = Man("", "");
}

Student::Student(std::string new_last_name, std::string new_name, std::string new_fac, int new_grup) :
	faculty(new_fac), grup(new_grup)
{
	man = Man(new_last_name, new_name);
	count++;
}

Student::Student(const Student& stud)
{
	man = stud.man;
	faculty = stud.faculty;
	grup = stud.grup;
}

std::istream& operator>>(std::istream& in, Student& stud)
{
	std::string tmp;
	std::cout << "Enter student's last name: ";
	std::cin >> tmp;
	stud.man.set_last_name(tmp);
	std::cout << "Enter student's name: ";
	std::cin >> tmp;
	stud.man.set_name(tmp);
	std::cout << "Enter student's faculty: ";
	std::cin >> stud.faculty;
	std::cout << "Enter student's group: ";
	std::cin >> stud.grup;
	return in;
}

std::ostream& operator<<(std::ostream& out, const Student& stud)
{
	std::cout.setf(std::ios::left);
	out << stud.man;
	out.width(30);
	out << stud.faculty;
	out.width(5);
	out << stud.grup;
	out << std::endl;
	return out;
}

bool Student::is_last_name(std::string str)
{
	return str == man.get_last_name();
}

void find_by_group_number(Student* student_base)
{
	int grup;
	int count = 0;

	std::cout << "Enter student's group: ";
	std::cin >> grup;

	for (size_t i = 0; i < Student::count; ++i)
	{
		if (grup == (student_base[i]).grup)
		{
			if (!count)
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
			}
			std::cout << student_base[i];
			++count;
		}
	}
	if (!count)
		std::cout << "Student is not found.\n";

}

void show_table(Student*);

void sort_by_name(Student* student_base)
{
	int size = Student::count;
	for (int step = size / 2; step > 0; step /= 2)
	{
		for (int i = step; i < size; ++i)
		{
			for (int j = i - step; j >= 0 && (student_base[j].man.get_last_name() > student_base[j + step].man.get_last_name() ||
				(student_base[j].man.get_last_name() == student_base[j + step].man.get_last_name() && student_base[j].man.get_name() > student_base[j + step].man.get_name())); j -= step)
			{
				Student tmp = student_base[j];
				student_base[j] = student_base[j + step];
				student_base[j + step] = tmp;
			}

		}
	}
	show_table(student_base);
}