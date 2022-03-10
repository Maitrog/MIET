#include "DeparturStationComparer.h"
#include "Ticket.h"

bool DeparturStationComparer::operator()(Ticket& tic1, Ticket& tic2) const
{
	return (tic1.get_departureStation() < tic2.get_departureStation());
}
