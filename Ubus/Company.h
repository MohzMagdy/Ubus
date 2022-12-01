#pragma once
#include "LinkedList.h"
#include "queue.h"
#include "Passengers.h"
#include "Buses.h"
#include "Event.h"

class Company {
private:
	queue<Event*> pEvents;
	queue<Passengers*> pPassengers;
	queue<Buses*> pBuses;

	int event_count = 0;
	int passenger_count = 0;
	int bus_count = 0;

public:
	Company() {}; // Default Constructor
	~Company() // Destructor
	{ // TEMPORARY: Should delete all pointers in lists
		delete &pEvents;
		delete &pPassengers;
		delete &pBuses;
	}

	// Getters
	int get_passenger_count()
	{
		return passenger_count;
	}

	// Add functions
	void add_event(Event* pEvent)
	{
		pEvents.Enqueue(pEvent);
		event_count++;
	}

	void add_passenger(Passengers* pPass)
	{
		pPassengers.Enqueue(pPass);
		passenger_count++;
	}

	void add_bus(Buses* pBus)
	{
		pBuses.Enqueue(pBus);
		bus_count++;
	}

	// Functions
	Passengers* find_passenger(int ID) // Returns pointer of passenger with given ID
	{
		bool found = false;
		Passengers* pPass = nullptr;
		Passengers* pHelper;
		for (int i = 0; i < passenger_count; i++) // Loop goes over whole queue to keep the order unchanged
		{
			pHelper = pPassengers.Dequeue();
			if (!found && pHelper->get_ID() == ID)
			{
				pPass = pHelper;
				found = true;
				
			}
			pPassengers.Enqueue(pHelper);
		}

		return pPass;
	}

	void delete_passenger(Passengers* pPass) 	
	{
		// Deleting passenger from passengers queue by dequeuing it
		bool found = false;
		Passengers* pHelper;

		for (int i = 0; i < passenger_count; i++) // Loop goes over whole queue to keep the order unchanged
		{
			pHelper = pPassengers.Dequeue();
			if (!found && pHelper == pPass)
			{
				delete pHelper;
				found = true;
			}
			else
			{
				pPassengers.Enqueue(pHelper);
			}
		}
		if(found) passenger_count--;

		// Removes hanging pointer for deleted passenger from all events
		Event* pEvent;
		for (int i = 0; i < event_count; i++) 
		{
			pEvent = pEvents.Dequeue();
			if (pEvent->get_pPass() == pPass) 
			{
				pEvent->set_pPass(nullptr); 
			}
			pEvents.Enqueue(pEvent);
		}
	}
};
