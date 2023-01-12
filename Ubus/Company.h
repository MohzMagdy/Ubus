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
#include <time.h>
#include "priority_queue.h"
#include "Time.h"


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
	queue<Passengers*> pDeliveredVIP;
	queue<Passengers*> pDeliveredSp;
	queue<Passengers*> pDeliveredNorm;

	UI* pUI;

	Time MaxW;
	Time Timestep;
	Time Autopromotionlimit;

	int  AutopromotionNumber;
	int no_checkup;
	
	int noNbus;
	int noSbus;
	int noVbus;

	bool ExecuteAvailableEvent(bool);
public:
	Company();
	~Company();
	bool checkexitstatus();
	void simulate();
	
	int checkQueueFront(queue<Buses*>);
	int checkBusFrontID(queue<Buses*>);

	void add_event(Event* PEvent);
	void add_ready(Passengers* pPass);
	void add_empty_bus(Buses* pBus);

	Passengers* pWaitNorm_find(int ID);
	void pWaitNorm_delete(Passengers* pPass);
	void promoteNorm(Passengers* pPass);
	
	void File_IO_Loading();

	void increaseMaxWforall(); /// Still need to add VIP passengers
	void maxqs(); /// passengers aren't removed from the queue
	
	
	void CheckAutopromotion();
	bool Isworkinghours();
	void deliver_passengers();
	void ExecuteDeliveryFailure();
	void DropBus();

	// Boarding passengers into bus
	void boardPassengers(Mode CurrentMode,bool isWorking);
	void boardVIP();
	void boardSp();
	void boardNorm();
	// Immediate boarding mode
	void immBoardVIP();
	void immBoardSp();
	void immBoardNorm();

	bool reachedMaxW(Passengers* pPass);

	void prioequation();

	void MoveBuses();
	int GetFarthestDeliveryDistance(queue<Passengers*>);
	int GetSumOfUnrideTime(queue<Passengers*>);
	void PrintInteractiveModeData();
	void maintinance_check();
	void incheck();
	void outputfile();

	string GetStatistcs();
};
