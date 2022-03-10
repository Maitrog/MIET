#pragma once
#include <iostream>
#include "Account.h"

class Credit: public Account
{
private:
	double credit;
	double percent;

public:
	static int count;

	Credit();
	Credit(Fio, int, double, double);
	Credit(const Credit&);

	virtual ~Credit();

	double get_credit();
	void set_credit(double);

	double get_percent();
	void set_percent(double);

	friend std::ostream& operator<<(std::ostream&, const Credit&);
	friend std::istream& operator>>(std::istream&, Credit&);

	virtual std::string info();
};