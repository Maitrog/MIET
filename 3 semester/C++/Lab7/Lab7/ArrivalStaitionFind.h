#pragma once
#include <string>
#include "Ticket.h"

class ArrivalStaitionFind
{
private:
	std::string staition;

public: 
	ArrivalStaitionFind(std::string);
	
	bool operator()(Ticket&) const;
};

