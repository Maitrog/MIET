#include "BaseTicket.h"


BaseTicket::BaseTicket()
{
	person = Fio();
	cost = 0.0;
}

BaseTicket::BaseTicket(Fio _person, double _cost)
{
	person = _person;
	cost = _cost;
}

BaseTicket::BaseTicket(std::string _name, std::string _lastName, std::string _secondName, double _cost)
{
	person = Fio(_name, _lastName, _secondName);
	cost = _cost;
}

BaseTicket::BaseTicket(const BaseTicket& _ticket)
{
	person = _ticket.person;
	cost = _ticket.cost;
}

BaseTicket::~BaseTicket() {}

Fio BaseTicket::get_fio()
{
	return person;
}

double BaseTicket::get_cost()
{
	return cost;
}

void BaseTicket::set_cost(double _cost)
{
	cost = _cost;
}