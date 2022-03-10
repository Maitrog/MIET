#pragma once
#include <iostream>
#include "Fio.h"
#include <string>

class Fio;

/*Класс билет*/
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

	Fio get_fio() const;

	std::string get_arrivalStantion() const;
	void set_arrivalStantion(std::string);

	std::string get_departureStation() const;
	void set_departureStation(std::string);

	double get_cost() const;
	void set_cost(double);

	bool findByArrivalStantion(std::string) const;

	friend Ticket* sortByDepartureStation(Ticket*);

	Ticket& operator=(const Ticket&);

	friend std::istream& operator>>(std::istream&, Ticket&);
	friend std::ostream& operator<<(std::ostream&, const Ticket&);

	friend bool operator==(const Ticket&, const Fio&);
};