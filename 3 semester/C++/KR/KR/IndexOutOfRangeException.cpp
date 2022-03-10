#include "IndexOutOfRangeException.h"


const char* IndexOutOfRangeException::what() const throw() { return "Index out of range."; }