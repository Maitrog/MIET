#pragma once
#include <iostream>
#include "Fio.h"

class Account
{
private:
	Fio name;
	int number;
public:
	Account();
	Account(Fio, int);
	Account(const Account&);

	virtual ~Account();

	Fio get_name();
	Fio get_name() const;

	void set_name(Fio);

	int get_number();
	int get_number() const;
	void set_number(int);

	friend std::ostream& operator<<(std::ostream&, const Account&);
	friend std::istream& operator>>(std::istream&, Account&);

	Account& operator=(const Account&);

	virtual std::string info() = 0;
};