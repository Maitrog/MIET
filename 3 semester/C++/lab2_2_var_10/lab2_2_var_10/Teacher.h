#pragma once
#include <iostream>
#include "Name.h"

class Teacher
{
private:
	int department;
	int status;
	Name fullName;

public:
	static int count;
	
	Teacher() : department(1), status(1), fullName(Name())
	{
		++count;
	}

	Teacher(int _dep, Name _name, int _st): department(_dep), status(_st), fullName(_name)
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

	Teacher& operator=(const Teacher&);


	int get_department() { return department; }
	void set_department(int _dep) { department = _dep; }

	Name get_fullName() { return fullName; }
	void set_fullName(Name _name) { fullName = _name; }

	int get_status() { return status; }
	void set_statud(int _st) { status = _st; }

	static void show_table(struct Teacher*, int);

	static void find_by_full_name(Teacher*, Name);

	friend void find_by_status(Teacher*, int);

	friend void sort_by_full_name(Teacher*, int);

	static Teacher* add_teacher(Teacher*,const Teacher&);

	bool operator==(const Teacher&);
};