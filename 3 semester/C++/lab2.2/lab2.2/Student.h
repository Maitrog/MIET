#pragma once
#include <string>
#include <vector>
#include "Man.h"


class Student
{
private:
	Man man;
	std::string faculty;
	int grup;
public:
	static int count;
	Student();

	Student(std::string new_last_name, std::string new_name, std::string new_fac, int new_grup);

	Student(const Student& stud);

	~Student()
	{
	}

	std::string get_faculty() const { return faculty; }
	void set_faculty(std::string str) { faculty = str; }

	int get_grup() const { return grup; }
	void set_grup(int g) { grup = g; }

	Man &get_man() { return man; }

	friend std::istream& operator>>(std::istream& in, Student& stud);

	friend std::ostream& operator<<(std::ostream& out, const Student& stud);

	friend void find_by_group_number(Student* student_base);

	friend void sort_by_name(Student* student_base);

	bool is_last_name(std::string);

};
