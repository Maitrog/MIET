#include <iostream>
#include "Name.h"

int isalphastr(std::string str, int size);

std::ostream& operator<<(std::ostream& out, const Name& _nm)
{
	std::cout.setf(std::ios::left);
	out.width(16);
	out << _nm.surname;
	out.width(16);
	out << _nm.name;
	out.width(16);
	out << _nm.secondname;
	return out;
}

std::istream& operator>>(std::istream& in, Name& _nm)
{
	do {
		std::cout << "Enter name: ";
		in >> _nm.name;
	} while (!isalphastr(_nm.name, _nm.name.length()));

	do {
	std::cout << "Enter surname: ";
	in >> _nm.surname;
	} while (!isalphastr(_nm.surname, _nm.surname.length()));

	do {
	std::cout << "Enter secondname: ";
	in >> _nm.secondname;
	return in;
	} while (!isalphastr(_nm.secondname, _nm.secondname.length()));
}

Name& Name::operator=(const Name& _nm)
{
	name = _nm.name;
	surname = _nm.surname;
	secondname = _nm.secondname;
	return *this;
}

bool Name::operator==(const Name& _nm)
{
	if (name == _nm.name && surname == _nm.surname && secondname == _nm.secondname)
		return true;
	return false;
}