#pragma once
#include <iostream>
#include "Fio.h"

class Bank
{
private:
	Fio name;
	int number;
	double deposit;
public:
	static int count;

	Bank();
	Bank(Fio, int, double);
	Bank(const Bank&);
	~Bank();

	Fio get_name();
	void set_name(Fio);

	int get_number();
	void set_number(int);

	double get_deposit();
	void set_deposit(double);

	friend std::ostream& operator<<(std::ostream&, const Bank&);
	friend std::istream& operator>>(std::istream&, Bank&);

	Bank& operator=(const Bank&);
	Bank& operator+(const int&);
};