#include "NullPtrException.h"


const char* NullPtrException::what() { return "Array pointer can't be nullptr"; }