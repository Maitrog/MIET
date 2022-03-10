#pragma once
#include <iostream>
#include <string>
#include "Fio.h"


class BaseTicket
{
protected:
	Fio person;
	double cost;
public:
	BaseTicket();
	BaseTicket(Fio, double);
	BaseTicket(std::string, std::string, std::string, double);
	BaseTicket(const BaseTicket&);

	virtual ~BaseTicket();

	Fio get_fio();

	double get_cost();
	void set_cost(double);

	virtual std::string info() = 0;
};