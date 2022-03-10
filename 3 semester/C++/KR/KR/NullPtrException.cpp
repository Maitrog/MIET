#include "NullPtrException.h"


const char* NullPtrException::what() const throw() { return "Array pointer can't be nullptr"; }