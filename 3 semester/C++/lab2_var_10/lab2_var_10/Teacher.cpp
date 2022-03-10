#include <iostream>
#include "Teacher.h"

int Teacher::count = 0;

void Teacher::find_by_full_name(Teacher* teacher_base, std::string _name)
{
	int count = 0;
	for (size_t i = 0; i < Teacher::count; ++i)
	{
		if (teacher_base[i].fullName == _name)
		{
			count++;
			if (count == 1)
			{
				std::cout << std::endl;
				std::cout.setf(std::ios::left);
				std::cout.width(11);
				std::cout << "Department";
				std::cout.width(51);
				std::cout << "Full name";
				std::cout.width(16);
				std::cout << "Status" << std::endl;
			}

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
	}
	if (!count)
	{
		std::cout << "Teacher not found.\n";
	}
}

void Teacher::show_table(Teacher* teacher_base, int size)
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

void find_by_status(Teacher* teacher_base, int _st)
{
	int count = 0;
	for (size_t i = 0; i < Teacher::count; ++i)
	{
		if (teacher_base[i].status == _st)
		{
			count++;
			if (count == 1)
			{
				std::cout << std::endl;
				std::cout.setf(std::ios::left);
				std::cout.width(11);
				std::cout << "Department";
				std::cout.width(51);
				std::cout << "Full name";
				std::cout.width(16);
				std::cout << "Status" << std::endl;
			}

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
	}
	if (!count)
	{
		std::cout << "Teacher not found.\n";
	}
}

void sort_by_full_name(Teacher* teacher_base, int count)
{
	int size = count;
	for (int step = size / 2; step > 0; step /= 2)
	{
		for (int i = step; i < size; ++i)
		{
			for (int j = i - step; j >= 0 && (teacher_base[j].fullName > teacher_base[j + step].fullName); j -= step)
			{
				Teacher tmp = teacher_base[j];
				teacher_base[j] = teacher_base[j + step];
				teacher_base[j + step] = tmp;
			}

		}
	}
	Teacher::show_table(teacher_base, count);
}

Teacher* Teacher::add_teacher(Teacher* teacher_base, const Teacher& new_teacher)
{
	Teacher* tmp = new Teacher[Teacher::count];
	for (int i = 0; i < (Teacher::count - 1) / 2; ++i)
	{
		tmp[i] = teacher_base[i];
	}
	delete[] teacher_base;
	teacher_base = tmp;
	teacher_base[Teacher::count - 2] = new_teacher;

	return teacher_base;
}