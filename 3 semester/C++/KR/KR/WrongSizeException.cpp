#include "WrongSizeException.h"


const char* WrongSizeException::what() const throw() { return "Size can't be negative."; }