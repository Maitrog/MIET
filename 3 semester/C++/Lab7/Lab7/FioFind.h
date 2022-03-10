#pragma once
#include "Fio.h"
#include "Ticket.h"
class FioFind
{
private:
	Fio fio;
public:
	FioFind(Fio);

	bool operator()(Ticket&) const;
};

