#include <iostream>
#include <string>
#include "Ticket.h"
#include "Fio.h"

int Ticket::count = 0;

Ticket::Ticket() :person(Fio()), arrivalStation(""), departureStation(""), cost(0.0) 
{
	count++;
}
Ticket::Ticket(Fio _fio, std::string _departureStation, std::string _arrivalStation, double _cost):
	person(_fio), departureStation(_departureStation), arrivalStation(_arrivalStation), cost(_cost) 
{
	count++;
}

Ticket::Ticket(std::string _name, std::string _lastName, std::string _secondName, std::string _departureStation, std::string _arrivalStation, double _cost) :
	person(_name, _lastName, _secondName), departureStation(_departureStation), arrivalStation(_arrivalStation), cost(_cost) 
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

Fio Ticket::get_fio() const
{
	return person;
}

std::string Ticket::get_arrivalStantion() const
{
	return arrivalStation;
}
void Ticket::set_arrivalStantion(std::string _arrivalStation)
{
	arrivalStation = _arrivalStation;
}

std::string Ticket::get_departureStation() const
{
	return departureStation;
}

void Ticket::set_departureStation(std::string _departureStation)
{
	departureStation = _departureStation;
}

double Ticket::get_cost() const
{
	return cost;
}
void Ticket::set_cost(double _cost)
{
	cost = _cost;
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
	in >> ticket.person;
	std::cout << "¬ведите пункт отправлени€: ";
	in >> ticket.departureStation;
	std::cout << "¬ведите пункт прибыти€: ";
	in >> ticket.arrivalStation;
	std::cout << "¬ведите цену билета: ";
	in >> ticket.cost;
	return in;
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

bool operator==(const Ticket& tic, const Fio& fio)
{
	return tic.get_fio() == fio;
}