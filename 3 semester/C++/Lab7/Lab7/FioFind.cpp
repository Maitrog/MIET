#include "FioFind.h"

FioFind::FioFind(Fio f):fio(f)
{}

bool FioFind::operator()(Ticket& tic) const
{
	return tic == fio;
}