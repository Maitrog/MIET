#pragma once
#include <iostream>
#include "Fio.h"
#include <string>
#include "BaseTicket.h"


class Ticket : public BaseTicket
{
private:
	std::string arrivalStation;
	std::string departureStation;

public:
	static int count;

	Ticket();
	Ticket(Fio, std::string, std::string, double);
	Ticket(std::string, std::string, std::string, std::string, std::string, double);
	Ticket(const Ticket&);

	virtual ~Ticket();

	std::string get_arrivalStantion();
	void set_arrivalStantion(std::string);

	std::string get_departureStation();
	void set_departureStation(std::string);

	bool findByArrivalStantion(std::string) const;

	friend Ticket* sortByDepartureStation(Ticket*);

	Ticket& operator=(const Ticket&);

	friend std::istream& operator>>(std::istream&, Ticket&);
	friend std::ostream& operator<<(std::ostream&, const Ticket&);

	bool operator==(const Fio&);

	virtual std::string info();
};