#include "WrongSizeException.h"


const char* WrongSizeException::what() { return "Size can't be negative."; }