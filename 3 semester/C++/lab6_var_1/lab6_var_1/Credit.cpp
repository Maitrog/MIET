#include "Credit.h"

int Credit::count = 0;

Credit::Credit() :Account()
{
	credit = 0;
	percent = 0;
	count++;
}
Credit::Credit(Fio _name, int _number, double _credit, double _percent, int _term) :Account(_name, _number)
{
	credit = _credit;
	percent = _percent;
	term = _term;
	monthlyPaymant = credit * (percent / 100 / 12 * std::pow((1 + percent / 100 / 12), term)) / (std::pow((1 + percent / 100 / 12), term) - 1);
	count++;
}
Credit::Credit(const Credit& _credit)
{
	this->set_name(_credit.get_name());
	this->set_number(_credit.get_number());
	credit = _credit.credit;
	percent = _credit.percent;
	term = _credit.term;
	monthlyPaymant = _credit.monthlyPaymant;
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

double Credit::get_monthlyPayment()
{
	return monthlyPaymant;
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
	out.width(10);
	out << _credit.term;
	out.width(10);
	out << _credit.monthlyPaymant;

	return out;
}
std::istream& operator>>(std::istream& in, Credit& _credit)
{
	int tmp;
	Fio _name;
	while (true)
	{
		try
		{
			std::cout << "Введите номер счёта: ";
			in >> tmp;
			if (in.fail())
			{
				in.clear();
				in.ignore(32768, '\n');
				throw std::invalid_argument("Ошибка ввода!");
			}
			else
			{
				if (tmp <= 0)
					throw std::invalid_argument("Номер счёта может быть только положительным числом");
				break;
			}
		}
		catch (std::invalid_argument &e)
		{
			std::cout << e.what() << std::endl;
			continue;
		}
	}
	_credit.set_number(tmp);


	while (true) 
	{
		try
		{
			in >> _name;
			break;
		}
		catch (std::bad_cast& e)
		{
			std::cerr << "В имени могут содержаться только буквы" << std::endl;
			continue;
		}
	}
	_credit.set_name(_name);


	while (true)
	{
		try
		{
			std::cout << "Введите сумму кредита: ";
			in >> _credit.credit;
			if (in.fail())
			{
				in.clear();
				in.ignore(32768, '\n');
				throw std::invalid_argument("Ошибка ввода!");
			}
			else
			{
				if (_credit.credit <= 0)
					throw std::invalid_argument("Сумма кредита должна принимать положительное значение");
				break;
			}
		}
		catch (std::invalid_argument& e)
		{
			std::cout << e.what() << std::endl;
			continue;
		}
	}

	while (true)
	{
		try
		{
			std::cout << "Введите процент по кредиту: ";
			in >> _credit.percent;
			if (in.fail())
			{
				in.clear();
				in.ignore(32768, '\n');
				throw std::invalid_argument("Ошибка ввода!");
			}
			else
			{
				if (_credit.percent <= 0)
					throw std::invalid_argument("Процент по кредиту должен принимать положительное значение");
				break;
			}
		}
		catch (std::invalid_argument& e)
		{
			std::cout << e.what() << std::endl;
			continue;
		}
	}

	while (true)
	{
		try
		{
			std::cout << "Введите срок кредита в месяцах: ";
			in >> _credit.term;
			if (in.fail())
			{
				in.clear();
				in.ignore(32768, '\n');
				throw std::invalid_argument("Ошибка ввода!");
			}
			else
			{
				if (_credit.term <= 0)
					throw std::invalid_argument("Срок кредита должен быть больше нуля");
				break;
			}
		}
		catch (std::invalid_argument& e)
		{
			std::cout << e.what() << std::endl;
			continue;
		}
	}

	_credit.monthlyPaymant = _credit.credit * (_credit.percent / 100 / 12 * std::pow((1 + _credit.percent / 100 / 12), _credit.term)) / (std::pow((1 + _credit.percent / 100 / 12), _credit.term) - 1);
	return in;
}

std::string Credit::info()
{
	std::string str = "";
	str += this->get_name().get_name() + " " + this->get_name().get_lastName() + " " + this->get_name().get_secondName() +
		"\nНомер счёта: " + std::to_string(this->get_number()) + " - " + "\nСумма кредита: " + std::to_string(credit) 
		+ "\nПроцент по кредиту: " + std::to_string(percent) + "\nСрок кредита: " + std::to_string(term) + "\nЕжемесячный платёж: " + std::to_string(monthlyPaymant);
	return str;
}