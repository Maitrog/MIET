#pragma once
#include <iostream>
#include "Fio.h"
#include <string>


class Ticket
{
private:
	Fio person;
	std::string arrivalStation;
	std::string departureStation;
	double cost;

public:
	static int count;

	Ticket();
	Ticket(Fio, std::string, std::string, double);
	Ticket(std::string, std::string, std::string, std::string, std::string, double);
	Ticket(const Ticket&);

	~Ticket();

	Fio get_fio();

	std::string get_arrivalStantion();
	void set_arrivalStantion(std::string);

	std::string get_departureStation();
	void set_departureStation(std::string);

	double get_cost();
	void set_cost(double);

	bool findByArrivalStantion(std::string) const;

	friend Ticket* sortByDepartureStation(Ticket*);

	Ticket& operator=(const Ticket&);

	friend std::istream& operator>>(std::istream&, Ticket&);
	friend std::ostream& operator<<(std::ostream&, const Ticket&);
};