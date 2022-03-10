#pragma once
#include <iostream>
#include <exception>


class DiscrepancySizeException : public std::exception
{
private:
	int sizeFirstArray;
	int sizeSecondArray;
	std::string exc;
public:
	DiscrepancySizeException(int, int);
	const char* what() const throw();
};