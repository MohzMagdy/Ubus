#pragma once
#include "Buses.h"
#include "Passengers.h"

class Event
{
public:
	Event() {};
	virtual void Execute() = 0;
};

