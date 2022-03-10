#include "Date.h"
#include <iostream>
#include <string>
#include <iomanip>

Date::Date() : day(1), month(1), year(0) {}
Date::Date(int _day, int _month, int _year) : day(_day), month(_month), year(_year) {}
Date::Date(const Date& _date)
{
	day = _date.day;
	month = _date.month;
	year = _date.year;
}

void Date::set_day(int _day)
{
	day = _day;
}
int Date::get_day()
{
	return day;
}

void Date::set_month(int _month)
{
	month = _month;
}
int Date::get_month()
{
	return month;
}

void Date::set_year(int _year)
{
	year = _year;
}
int Date::get_year()
{
	return year;
}

bool Date::operator==(const Date& _date)
{
	return day == _date.day && month == _date.month && year == _date.year;
}
bool Date::operator>(const Date& _date)
{
	return year > _date.year || year == _date.year && month > _date.month || year == _date.year && month == _date.month && day > _date.day;
}
bool Date::operator<(const Date& _date)
{
	return year < _date.year || year == _date.year && month < _date.month || year == _date.year && month == _date.month && day < _date.day;
}
bool Date::operator!=(const Date& _date)
{
	return !(*this == _date);
}

Date& Date::operator=(const Date& _date)
{
	day = _date.day;
	month = _date.month;
	year = _date.year;
	return *this;
}
std::istream& operator>>(std::istream& in, Date& _date)
{
	std::string date;
	in >> date;
	if (date[2] == date[5] && date[2] == '.')
	{
		_date.day = atoi(date.substr(0, 2).c_str());
		_date.month = atoi(date.substr(3, 2).c_str());
		_date.year = atoi(date.substr(6, 4).c_str());
	}
	if (date[1] == date[4] && date[1] == '.')
	{
		_date.day = atoi(date.substr(0, 1).c_str());
		_date.month = atoi(date.substr(2, 2).c_str());
		_date.year = atoi(date.substr(5, 4).c_str());
	}
	if (date[1] == date[3] && date[1] == '.')
	{
		_date.day = atoi(date.substr(0, 1).c_str());
		_date.month = atoi(date.substr(2, 1).c_str());
		_date.year = atoi(date.substr(4, 4).c_str());
	}
	if (date[2] == date[4] && date[2] == '.')
	{
		_date.day = atoi(date.substr(0, 2).c_str());
		_date.month = atoi(date.substr(3, 1).c_str());
		_date.year = atoi(date.substr(5, 4).c_str());
	}
	if ((_date.month > 12 || _date.month < 1) || _date.day < 1 || (_date.day > 31 && (_date.month == 1 || _date.month == 3 || _date.month == 5 || _date.month == 7 ||
		_date.month == 8 || _date.month == 10 || _date.month == 12)) || (_date.day > 30 && (_date.month == 4 || _date.month == 6 || _date.month == 9 ||
			_date.month == 11)) || (_date.day > 28 && _date.month == 2 && _date.year % 4 == 0))
		throw std::invalid_argument("Неверный ввод даты");
	return in;
}
std::ostream& operator<<(std::ostream& out, Date& _date)
{
	out << _date.day << '.' << _date.month << '.' << _date.year;
	return out;
}