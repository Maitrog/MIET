#include "Bank.h"

int Bank::count = 0;

Bank::Bank()
{
	name = Fio();
	number = -1;
	deposit = 0;
	count++;
}
Bank::Bank(Fio _name, int _number, double _deposit):name(_name), number(_number), deposit(_deposit)
{
	count++;
}
Bank::Bank(const Bank& _bank)
{
	name = _bank.name;
	number = _bank.number;
	deposit = _bank.deposit;
	count++;
}

Bank::~Bank()
{
	count--;
}

Fio Bank::get_name()
{
	return name;
}
void Bank::set_name(Fio _name)
{
	name = _name;
}

int Bank::get_number()
{
	return number;
}
void Bank::set_number(int _number)
{
	number = _number;
}

double Bank::get_deposit()
{
	return deposit;
}
void Bank::set_deposit(double _deposit)
{
	deposit = _deposit;
}

std::ostream& operator<<(std::ostream& out, const Bank& _bank)
{
	std::cout.setf(std::ios::left);
	out.width(15);
	out << _bank.number << _bank.name;
	out.width(30);
	out << _bank.deposit;
	return out;
}
std::istream& operator>>(std::istream& in, Bank& _bank)
{
	while (true)
	{
		std::cout << "¬ведите номер счЄта: ";
		in >> _bank.number;
		if (in.fail())
		{
			in.clear();
			in.ignore(32768, '\n');
			std::cout << "ќшибка ввода!\n";
		}
		else
			break;
	}
	in >> _bank.name;
	while (true)
	{
		std::cout << "¬ведите сумму депозита: ";
		in >> _bank.deposit;
		if (in.fail())
		{
			in.clear();
			in.ignore(32768, '\n');
			std::cout << "ќшибка ввода!\n";
		}
		else
			break;
	}
	return in;

}

Bank& Bank::operator=(const Bank& _bank)
{
	name = _bank.name;
	number = _bank.number;
	deposit = _bank.deposit;
	return *this;
}
Bank& Bank::operator+(const int& money)
{
	deposit += money;

	return *this;
}