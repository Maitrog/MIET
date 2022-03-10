#include "Fio.h"
#include <cstring>

bool isalpha(std::string& str)
{
	for (int i = 0; i < str.size(); i++)
		if (!(str[i] <= 'z' && str[i] >= 'a' || str[i] >= 'A' && str[i] <= 'Z' || str[i] >= 'а' && str[i] <= 'я' || str[i] >= 'А' && str[i] <= 'Я'))
			return false;
	return true;
}

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
	std::cout << "Введите имя: ";
	in >> fio.name;
	if (!isalpha(fio.name))
		throw std::bad_cast();
	std::cout << "Введите фамилию: ";
	in >> fio.lastName;
	if (!isalpha(fio.lastName))
		throw std::bad_cast();
	std::cout << "Введите отчество: ";
	in >> fio.secondName;
	if (!isalpha(fio.secondName))
		throw std::bad_cast();
	return in;
}

Fio& Fio::operator=(const Fio& fio)
{
	name = fio.name;
	lastName = fio.lastName;
	secondName = fio.secondName;
	return *this;
}

bool Fio::operator==(const Fio& _fio)
{
	if (name == _fio.name && lastName == _fio.lastName && secondName == _fio.secondName)
		return true;
	return false;
}