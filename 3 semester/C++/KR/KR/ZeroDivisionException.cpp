#include <iostream>
#include <exception>
#include "ZeroDivisionException.h"

const char* ZeroDivisionException::what() const throw() { return "ZeroDivisionException"; }