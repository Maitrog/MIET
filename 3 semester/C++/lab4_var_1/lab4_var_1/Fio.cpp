#include "Fio.h"

Fio::Fio()
{
	name = "";
	lastName = "";
	secondName = "";
}

Fio::Fio(std::string _name, std::string _lastName, std::string _secondName) :name(_name), lastName(_lastName), secondName(_secondName)
{}

Fio::Fio(const Fio& fio)
{
	name = fio.name;
	lastName = fio.lastName;
	secondName = fio.secondName;
}

std::string Fio::get_name()
{
	return name;
}
void Fio::set_name(std::string _name)
{
	name = _name;
}

std::string Fio::get_lastName()
{
	return lastName;
}
void Fio::set_lastName(std::string _lastName)
{
	lastName = _lastName;
}

std::string Fio::get_secondName()
{
	return secondName;
}
void Fio::set_secondName(std::string _secondName)
{
	secondName = _secondName;
}

std::ostream& operator<<(std::ostream& out, const Fio& fio)
{
	std::cout.setf(std::ios::left);
	out.width(30);
	out << fio.lastName;
	out.width(30);
	out << fio.name;
	out.width(30);
	out << fio.secondName;
	return out;
}

std::istream& operator>>(std::istream& in, Fio& fio)
{
	std::cout << "¬ведите им€: ";
	in >> fio.name;
	std::cout << "¬ведите фамилию: ";
	in >> fio.lastName;
	std::cout << "¬ведите отчество: ";
	in >> fio.secondName;
	return in;
}

Fio& Fio::operator=(const Fio& fio)
{
	name = fio.name;
	lastName = fio.lastName;
	secondName = fio.secondName;
	return *this;
}