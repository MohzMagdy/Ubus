#pragma once
#include "Buses.h"
#include "Passengers.h"

class Event
{
protected:
	// Should store event time and related passenger info
public:
	Event() {};
	virtual void getParameters() = 0;
	virtual void Execute() = 0;
};

