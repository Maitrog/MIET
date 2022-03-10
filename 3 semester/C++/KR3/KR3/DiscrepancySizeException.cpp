#include "DiscrepancySizeException.h"
#include <string>


DiscrepancySizeException::DiscrepancySizeException(int size1, int size2) :sizeFirstArray(size1), sizeSecondArray(size2) 
{}

std::string DiscrepancySizeException::what()
{
	std::string str;
	str = "Discrepancy array size. Size of first array: " + std::to_string(sizeFirstArray) + ". Size of second array: " + std::to_string(sizeSecondArray);
	return str;
}