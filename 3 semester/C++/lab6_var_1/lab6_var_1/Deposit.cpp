#include "Deposit.h"

int Deposit::count = 0;

Deposit::Deposit() :Account()
{
	deposit = 0;
	count++;
}
Deposit::Deposit(Fio _name, int _number, double _deposit) : Account(_name, _number), deposit(_deposit)
{
	count++;
}
Deposit::Deposit(const Deposit& _deposit)
{
	this->set_name(_deposit.get_name());
	this->set_number(_deposit.get_number());
	deposit = _deposit.deposit;
	count++;
}

Deposit::~Deposit()
{
	count--;
}

double Deposit::get_deposit()
{
	return deposit;
}
void Deposit::set_deposit(double _deposit)
{
	deposit = _deposit;
}

std::ostream& operator<<(std::ostream& out, const Deposit& _deposit)
{
	std::cout.setf(std::ios::left);
	out.width(15);
	out << _deposit.get_number() << _deposit.get_name();
	out.width(10);
	out << _deposit.deposit;
	return out;
}
std::istream& operator>>(std::istream& in, Deposit& _deposit)
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
		catch (std::invalid_argument& e)
		{
			std::cout << e.what() << std::endl;
			continue;
		}
	}
	_deposit.set_number(tmp);


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
	_deposit.set_name(_name);


	while (true)
	{
		try
		{
			std::cout << "Введите сумму депозита: ";
			in >> _deposit.deposit;
			if (in.fail())
			{
				in.clear();
				in.ignore(32768, '\n');
				throw std::invalid_argument("Ошибка ввода!");
			}
			else
			{
				if (_deposit.deposit <= 0)
					throw std::invalid_argument("Сумма депозита должна принимать положительное значение");
				break;
			}
		}
		catch (std::invalid_argument& e)
		{
			std::cout << e.what() << std::endl;
			continue;
		}
	}
	return in;

}

Deposit& Deposit::operator=(const Deposit& _deposit)
{
	this->set_name(_deposit.get_name());
	this->set_number(_deposit.get_number());
	deposit = _deposit.deposit;
	return *this;
}
Deposit& Deposit::operator+(const int& money)
{
	deposit += money;

	return *this;
}


std::string Deposit::info()
{
	std::string str = "";
	str += this->get_name().get_name() + " " + this->get_name().get_lastName() + " " + this->get_name().get_secondName() +
		"\nНомер счёта: " + std::to_string(this->get_number()) + " - " + "\nСумма депозита: " + std::to_string(deposit);
	return str;
}