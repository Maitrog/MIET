#include "Credit.h"

int Credit::count = 0;

Credit::Credit() :Account()
{
	credit = 0;
	percent = 0;
	count++;
}
Credit::Credit(Fio _name, int _number, double _credit, double _percent):Account(_name, _number)
{
	credit = _credit;
	percent = _percent;
	count++;
}
Credit::Credit(const Credit& _credit)
{
	this->set_name(_credit.get_name());
	this->set_number(_credit.get_number());
	credit = _credit.credit;
	percent = _credit.percent;
	count++;
}

Credit::~Credit()
{
	count--;
}

double Credit::get_credit()
{
	return credit;
}
void Credit::set_credit(double _cr)
{
	credit = _cr;
}

double Credit::get_percent()
{
	return percent;
}
void Credit::set_percent(double _per)
{
	percent = _per;
}

std::ostream& operator<<(std::ostream& out, const Credit& _credit)
{
	std::cout.setf(std::ios::left);
	out.width(15);
	out << _credit.get_number() << _credit.get_name();
	out.width(15);
	out << _credit.credit;
	out.width(10);
	out << _credit.percent;
	return out;
}
std::istream& operator>>(std::istream& in, Credit& _credit)
{
	int tmp;
	Fio _name;
	while (true)
	{
		std::cout << "Введите номер счёта: ";
		in >> tmp;
		if (in.fail())
		{
			in.clear();
			in.ignore(32768, '\n');
			std::cout << "Ошибка ввода!\n";
		}
		else
			break;
	}
	_credit.set_number(tmp);
	in >> _name;
	_credit.set_name(_name);
	while (true)
	{
		std::cout << "Введите сумму кредита: ";
		in >> _credit.credit;
		if (in.fail())
		{
			in.clear();
			in.ignore(32768, '\n');
			std::cout << "Ошибка ввода!\n";
		}
		else
			break;
	}

	while (true)
	{
		std::cout << "Введите процент по кредиту: ";
		in >> _credit.percent;
		if (in.fail())
		{
			in.clear();
			in.ignore(32768, '\n');
			std::cout << "Ошибка ввода!\n";
		}
		else
			break;
	}
	return in;
}

std::string Credit::info()
{
	std::string str = "";
	str += this->get_name().get_name() + " " + this->get_name().get_lastName() + " " + this->get_name().get_secondName() +
		"\nНомер счёта: " + std::to_string(this->get_number()) + " - " + "\nСумма кредита: " + std::to_string(credit) + "\nПроцент по кредиту" + std::to_string(percent);
	return str;
}