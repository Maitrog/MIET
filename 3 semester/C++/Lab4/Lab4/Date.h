#pragma once
#include <iostream>


class Date
{
private:
	int day;
	int month;
	int year;
public:
	Date();
	Date(int, int, int);
	Date(const Date&);

	void set_day(int);
	int get_day();

	void set_month(int);
	int get_month();

	void set_year(int);
	int get_year();

	bool operator==(const Date&);
	bool operator>(const Date&);
	bool operator<(const Date&);
	bool operator!=(const Date&);
	Date& operator=(const Date&);

	friend std::istream& operator>>(std::istream& in, Date& _date);
	friend std::ostream& operator<<(std::ostream& out, Date& _date);

};