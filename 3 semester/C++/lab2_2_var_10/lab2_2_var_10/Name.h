#pragma once
#include <iostream>


class Name
{
private:
	std::string name;		//имя
	std::string surname;	//фамилия
	std::string secondname;	//отчество

public:
	Name() : name(""), surname(""), secondname("")
	{};

	Name(std::string _name, std::string _surname, std::string _secondname) : name(_name), surname(_surname), secondname(_secondname)
	{};

	Name(std::string fullName)
	{
		std::string fn[3];
		fn[0] = "";
		fn[1] = "";
		fn[2] = "";
		for (int i = 0, j = 0; i < fullName.length(); i++)
		{
			if (fullName[i] != ' ')
				fn[j] += fullName[i];
			else if(j < 2)
				j++;
		}
		name = fn[1];
		surname = fn[0];
		secondname = fn[2];
	}

	Name(const Name& _nm)
	{
		name = _nm.name;
		surname = _nm.surname;
		secondname = _nm.secondname;
	}

	std::string get_name() { return name; }
	void set_name(std::string _name) { name = _name; }

	std::string get_surnamr() { return surname; }
	void set_surname(std::string _surname) { surname = _surname; }

	std::string get_secondname() { return secondname; }
	void set_secondname(std::string _secondname) { secondname = _secondname; }

	friend std::ostream& operator<<(std::ostream&, const Name&);
	friend std::istream& operator>>(std::istream&, Name&);

	Name& operator=(const Name&);

	bool operator==(const Name&);
};