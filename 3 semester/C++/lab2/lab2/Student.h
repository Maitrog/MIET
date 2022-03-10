#pragma once
#include <string>
#include <vector>
#include <iostream>


class Student
{
private:
	std::string fam;
	std::string name;
	std::string faculty;
	int grup;
public:
	static int count;
	Student() :fam(""), name(""), faculty(""), grup(0) 
	{
		++count;
	}

	Student(std::string new_name, std::string new_fam, std::string new_fac, int new_grup) :
		fam(new_fam), name(new_name), faculty(new_fac), grup(new_grup)
	{
		count++;
	}

	~Student()
	{
		--count;
	}
	std::string get_fam() const { return fam; };
	void set_fam(std::string str) { fam = str; }

	std::string get_name() const { return name; }
	void set_name(std::string str) { name = str; }

	std::string get_faculty() const { return faculty; }
	void set_faculty(std::string str) { faculty = str; }

	int get_grup() const { return grup; }
	void set_grup(int g) { grup = g; }

	friend std::ostream& operator<<(std::ostream& out, const Student& stud);

	friend void find_by_group_number(Student*);

	friend void sort_by_name(Student*);

	bool is_fam(std::string);

};
