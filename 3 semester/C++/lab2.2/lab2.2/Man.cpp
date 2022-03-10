#include "Man.h"
#include <iostream>

Man::Man() :name(""), last_name("") {}

Man::Man(std::string new_last_name, std::string new_name) :last_name(new_last_name), name(new_name) {}

Man::Man(const Man& man)
{
	last_name = man.last_name;
	name = man.name;
}

std::string Man::get_last_name() const 
{ 
	return last_name; 
};

void Man::set_last_name(std::string str) 
{ 
	last_name = str; 
}

std::string Man::get_name() const 
{ 
	return name; 
}

void Man::set_name(std::string str) 
{
	name = str; 
}

std::ostream& operator<<(std::ostream& out, const Man& man)
{
	std::cout.setf(std::ios::left);
	out.width(30);
	out << man.last_name;
	out.width(30);
	out << man.name;
	return out;
}