#pragma once
#include <iostream>

class Teacher
{
private:
	int department;
	std::string fullName;
	int status;

public:
	static int count;
	
	Teacher() : department(1), status(1), fullName("")
	{
		++count;
	}

	Teacher(int _dep, std::string _name, int _st): department(_dep), status(_st), fullName(_name)
	{
		++count;
	};

	Teacher(const Teacher& _teacher) 
	{
		department = _teacher.department;
		status = _teacher.status;
		fullName = _teacher.fullName;
		count++;
	};

	~Teacher()
	{
		count--;
	}

	int get_department() { return department; }
	void set_department(int _dep) { department = _dep; }

	std::string get_fullName() { return fullName; }
	void set_fullName(std::string _name) { fullName = _name; }

	int get_status() { return status; }
	void set_statud(int _st) { status = _st; }

	static void show_table(struct Teacher*, int);

	static void find_by_full_name(Teacher*, std::string);

	friend void find_by_status(Teacher*, int);

	friend void sort_by_full_name(Teacher*, int);

	static Teacher* add_teacher(Teacher*,const Teacher&);
};