#pragma once
#include "LinkedList.h"
#include "Passengers.h"
#include "Buses.h"
#include "Event.h"

class Company {
private:
	LinkedList<Event*> pEvents;
	LinkedList<Passengers*> pPassengers;
	LinkedList<Buses*> pBuses;

public:
	Company() {}; // Default Constructor

	void add_event(Event* pEvent)
	{
		pEvents.insert_end(pEvent);
	}

	void add_passenger(Passengers* pPass)
	{
		pPassengers.insert_end(pPass);
	};
};
