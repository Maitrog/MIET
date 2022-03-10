#include "Account.h"

Account::Account()
{
	name = Fio();
	number = -1;
}

Account::Account(Fio _name, int _number)
{
	name = _name;
	number = _number;
}
Account::Account(const Account& _acc)
{
	name = _acc.name;
	number = _acc.number;
}

Account::~Account() {}

Fio Account::get_name()
{
	return name;
}

Fio Account::get_name() const
{
	return name;
}

void Account::set_name(Fio _name)
{
	name = _name;
}

int Account::get_number()
{
	return number;
}

int Account::get_number() const
{
	return number;
}

void Account::set_number(int _number)
{
	number = _number;
}

std::ostream& operator<<(std::ostream& out, const Account& _acc)
{
	std::cout.setf(std::ios::left);
	out.width(15);
	out << _acc.number;
	out << _acc.name;
	return out;
}
std::istream& operator>>(std::istream& in, Account& _acc)
{
	while (true)
	{
		try
		{
			std::cout << "Введите номер счёта: ";
			in >> _acc.number;
			if (in.fail())
			{
				in.clear();
				in.ignore(32768, '\n');
				std::cout << "Ошибка ввода!\n";
			}
			else
				break;
			in >> _acc.name;

			return in;
		}
		catch (std::bad_cast& e)
		{
			std::cerr << "В имени могут содержаться только буквы" << std::endl;
			continue;
		}
	}
}

Account& Account::operator=(const Account& _acc)
{
	name = _acc.name;
	number = _acc.number;
	return *this;
}