#pragma once
#include "LinkedList.h"
#include "queue.h"
#include "Passengers.h"
#include "Buses.h"
#include "Event.h"
#include "Defs.h"
#include "ReadyEvent.h"
#include "PromoteEvent.h"
#include "CancelEvent.h"
#include "UI.h"
#include <sstream>
#include <string>
#include <fstream>
#include "priority_queue.h"


class Company {
private:
	queue<Event*> pEvents;

	// Passenger lists
	priority_queue<Passengers*> pWaitVIP;
	queue<Passengers*> pWaitSp;
	LinkedList<Passengers*> pWaitNorm;
	queue<Passengers*> pDelivered;

	// Bus lists
	queue<Buses*> pEmptyVIP;
	queue<Buses*> pEmptySp;
	queue<Buses*> pEmptyNorm;
	priority_queue<Buses*> pMoving;
	queue<Buses*> pCheckupVIP;
	queue<Buses*> pCheckupSp;
	queue<Buses*> pCheckupNorm;

	UI* pUI;

public:
	Company();
	~Company();

	void add_event(Event* PEvent);
	void add_ready(Passengers* pPass);
	void add_empty_bus(Buses* pBus);

	Passengers* pWaitNorm_find(int ID);
	void pWaitNorm_delete(Passengers* pPass);
	void promoteNorm(Passengers* pPass);
	
	void File_IO_Loading();
};
