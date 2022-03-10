#pragma once
#include <iostream>
#include <exception>


class WrongSizeException : public std::exception
{
public:
	const char* what();
};