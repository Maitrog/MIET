#pragma once
#include <iostream>
#include <exception>


class ZeroDivisionException : public std::exception
{
public:
	const char* what() const throw();
};