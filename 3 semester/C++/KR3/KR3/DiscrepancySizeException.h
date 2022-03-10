#pragma once
#include <iostream>
#include <exception>


class DiscrepancySizeException : public std::exception
{
private:
	int sizeFirstArray;
	int sizeSecondArray;
public:
	DiscrepancySizeException(int, int);
	std::string what();
};