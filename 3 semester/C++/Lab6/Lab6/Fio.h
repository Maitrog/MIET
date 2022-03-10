#pragma once
#include <iostream>
#include <string>

class Fio
{
private:
	std::string name;
	std::string lastName;
	std::string secondName;

public:
	Fio();
	Fio(std::string, std::string, std::string);
	Fio(const Fio&);

	std::string get_name();
	void set_name(std::string);

	std::string get_lastName();
	void set_lastName(std::string);

	std::string get_secondName();
	void set_secondName(std::string);

	friend std::ostream& operator<<(std::ostream&, const Fio&);
	friend std::istream& operator>>(std::istream&, Fio&);

	Fio& operator=(const Fio&);

	bool operator==(const Fio&);
};