#pragma once
#include <iostream>
#include <exception>


class IndexOutOfRangeException : public std::exception
{
public:
	const char* what();
};
