#pragma once
#include "BaseTicket.h"
#include "Date.h"
#include <iostream>

class Ticket2 :public BaseTicket
{
private:
	int wagonNoumber;
	int placeNoumber;
	Date date;
public:
	static int count;
	Ticket2();
	Ticket2(Fio, int, int, double, Date);
	Ticket2(std::string, std::string, std::string, int, int, double, Date);
	Ticket2(const Ticket2&);

	virtual ~Ticket2();

	int get_wagonNoumber();
	void set_wagonNoumber(int);

	int get_placeNoumber();
	void set_placeNoumber(int);

	Date get_date();
	void set_date(Date);

	friend std::istream& operator>>(std::istream&, Ticket2&);
	friend std::ostream& operator<<(std::ostream&, Ticket2&);

	virtual std::string info();

};