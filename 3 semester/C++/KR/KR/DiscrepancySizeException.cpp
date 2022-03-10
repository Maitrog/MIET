#include "DiscrepancySizeException.h"
#include <string>


DiscrepancySizeException::DiscrepancySizeException(int size1, int size2) :sizeFirstArray(size1), sizeSecondArray(size2)
{
	exc = "Discrepancy array size. Size of first array: " + std::to_string(sizeFirstArray) + ". Size of second array: " + std::to_string(sizeSecondArray);
}

const char* DiscrepancySizeException::what() const throw()
{
	return exc.c_str();
}