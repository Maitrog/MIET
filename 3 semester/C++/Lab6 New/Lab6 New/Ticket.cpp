#include <iostream>
#include <string>
#include "Ticket.h"

int Ticket::count = 0;

Ticket::Ticket() : BaseTicket(Fio(), 0.0), arrivalStation(""), departureStation("")
{
	count++;
}
Ticket::Ticket(Fio _fio, std::string _departureStation, std::string _arrivalStation, double _cost):
	BaseTicket(_fio, _cost), departureStation(_departureStation), arrivalStation(_arrivalStation)
{
	count++;
}

Ticket::Ticket(std::string _name, std::string _lastName, std::string _secondName, std::string _departureStation, std::string _arrivalStation, double _cost) :
	BaseTicket(_name, _lastName, _secondName, _cost), departureStation(_departureStation), arrivalStation(_arrivalStation)
{
	count++;
}

Ticket::Ticket(const Ticket& _ticket)
{
	person = _ticket.person;
	departureStation = _ticket.departureStation;
	arrivalStation = _ticket.arrivalStation;
	cost = _ticket.cost;
	count++;
}

Ticket::~Ticket()
{
	count--;
}


std::string Ticket::get_arrivalStantion()
{
	return arrivalStation;
}
void Ticket::set_arrivalStantion(std::string _arrivalStation)
{
	arrivalStation = _arrivalStation;
}

std::string Ticket::get_departureStation()
{
	return departureStation;
}
void Ticket::set_departureStation(std::string _departureStation)
{
	departureStation = _departureStation;
}

bool Ticket::findByArrivalStantion(std::string _arrivalStation) const
{
	if (arrivalStation == _arrivalStation)
		return true;
	return false;
}

Ticket& Ticket::operator=(const Ticket& _ticket)
{
	person = _ticket.person;
	arrivalStation = _ticket.arrivalStation;
	departureStation = _ticket.departureStation;
	cost = _ticket.cost;
	return *this;
}

std::istream& operator>>(std::istream& in, Ticket& ticket)
{
	while (true)
	{
		try
		{
			in >> ticket.person;
			std::cout << "Введите пункт отправления: ";
			in >> ticket.departureStation;
			std::cout << "Введите пункт прибытия: ";
			in >> ticket.arrivalStation;
			std::cout << "Введите цену билета: ";
			in >> ticket.cost;
			if (ticket.cost < 0.1)
				throw std::invalid_argument("Цена не может быть меньше 0.1");
			return in;
		}
		catch (std::bad_cast& e)
		{
			std::cerr << "В имени могут содержаться только буквы" << std::endl;
			continue;
		}
		catch (std::invalid_argument e)
		{
			std::cout << e.what() << std::endl;
			continue;
		}
	}
}
std::ostream& operator<<(std::ostream& out, const Ticket& ticket)
{
	//std::cout.setf(std::ios::left);
	out.width(30);
	out << ticket.person;
	out.width(30);
	out << ticket.departureStation;
	out.width(30);
	out << ticket.arrivalStation;
	out.width(10);
	out << ticket.cost << std::endl;
	return out;
}

std::string Ticket::info()
{
	std::string str = "";
	str += person.get_name() + " " + person.get_lastName() + " " + person.get_secondName() + 
		"\nСтанция отправления: " + departureStation + " - " + "\nСтанция прибытия: " + arrivalStation + "\nЦена: " + std::to_string(cost);
	return str;
}

bool Ticket::operator==(const Fio& fio)
{
	if (this->get_fio() == fio)
		return true;
	return false;
}