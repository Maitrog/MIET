#include "Ticket2.h"
#include <iomanip>

int Ticket2::count = 0;

Ticket2::Ticket2() :BaseTicket(), wagonNoumber(0), placeNoumber(0) 
{
	count++;
}

Ticket2::Ticket2(Fio _person, int _wagonNoumber, int _placeNoumber, double _cost, Date _date) :
	BaseTicket(_person, _cost), wagonNoumber(_wagonNoumber), placeNoumber(_placeNoumber), date(_date) 
{
	count++;
}

Ticket2::Ticket2(std::string _name, std::string _lastName, std::string _secondName, int _wagonNoumber, int _placeNoumber, double _cost, Date _date) :
	BaseTicket(_name, _lastName, _secondName, _cost), wagonNoumber(_wagonNoumber), placeNoumber(_placeNoumber), date(_date) 
{
	count++;
}

Ticket2::Ticket2(const Ticket2& _ticket)
{
	person = _ticket.person;
	placeNoumber = _ticket.placeNoumber;
	wagonNoumber = _ticket.wagonNoumber;
	cost = _ticket.cost;
	date = _ticket.date;
	count++;
}

Ticket2::~Ticket2() 
{
	count--;
}

int Ticket2::get_wagonNoumber()
{
	return wagonNoumber;
}
void Ticket2::set_wagonNoumber(int _wagonNoumber)
{
	wagonNoumber = _wagonNoumber;
}

int Ticket2::get_placeNoumber()
{
	return placeNoumber;
}
void Ticket2::set_placeNoumber(int _placeNoumber)
{
	placeNoumber = _placeNoumber;
}

Date Ticket2::get_date()
{
	return date;
}
void Ticket2::set_date(Date _date)
{
	date = _date;
}

std::istream& operator>>(std::istream& in, Ticket2& ticket)
{
	in >> ticket.person;
	std::cout << "Введите номер вагона: ";
	in >> ticket.wagonNoumber;
	std::cout << "Введите номер места: ";
	in >> ticket.placeNoumber;
	std::cout << "Введите цену билета: ";
	in >> ticket.cost;
	std::cout << "Введите дату поездки в формате ДД.ММ.ГГГГ: ";
	in >> ticket.date;
	return in;
}
std::ostream& operator<<(std::ostream& out, Ticket2& ticket)
{
	out.width(30);
	out  << ticket.person;
	out.width(14);
	out << ticket.wagonNoumber;
	out.width(13);
	out << ticket.placeNoumber;
	out.width(12);
	out << ticket.cost;
	//out.width(15);
	out << '\t' << ticket.date << std::endl;
	return out;
}

std::string Ticket2::info()
{
	std::string str = "";
	str += person.get_name() + " " + person.get_lastName() + " " + person.get_secondName() + "\n" +
		"Номер вагона: " + std::to_string(wagonNoumber) + '\n' + "Номер места: " + std::to_string(placeNoumber) + '\n' + "Цена: " + std::to_string(cost);
	return str;
}