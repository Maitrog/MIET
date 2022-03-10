#include "ArrivalStaitionFind.h"

ArrivalStaitionFind::ArrivalStaitionFind(std::string st): staition(st)
{}

bool ArrivalStaitionFind::operator()(Ticket& tic) const
{
	return tic.get_arrivalStantion() == staition;
}