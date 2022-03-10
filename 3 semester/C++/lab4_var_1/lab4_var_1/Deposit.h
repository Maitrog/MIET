#pragma once
#include <iostream>
#include "Account.h"


class Deposit: public Account
{
private:
	double deposit;
public:
	static int count;

	Deposit();
	Deposit(Fio, int, double);
	Deposit(const Deposit&);
	virtual ~Deposit();

	double get_deposit();
	void set_deposit(double);

	friend std::ostream& operator<<(std::ostream&, const Deposit&);
	friend std::istream& operator>>(std::istream&, Deposit&);

	Deposit& operator=(const Deposit&);
	Deposit& operator+(const int&);

	virtual std::string info();
};