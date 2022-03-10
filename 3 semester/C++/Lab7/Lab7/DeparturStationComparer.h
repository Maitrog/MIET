#pragma once
#include "Ticket.h"

class DeparturStationComparer
{
public:
	bool operator()(Ticket&, Ticket&) const;
};

