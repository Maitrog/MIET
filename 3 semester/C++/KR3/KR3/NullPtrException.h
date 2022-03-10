#pragma once
#include <iostream>
#include <exception>


class NullPtrException : public std::exception
{
public:
	const char* what();
};