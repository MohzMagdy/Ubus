#include "ReadyEvent.h"
#include "Company.h"
#include <stdio.h>
#include <string.h>

ReadyEvent::ReadyEvent(Company* pComp,Passenger_Type pType,Time EventTime, int ID, double distance, double totalRideUnride_Time, double cost)
{
	this->pComp = pComp;
	this->Ptype = pType;
	this->ID = ID;
	this->EventTime = EventTime;
	this->Delivery_distance = distance;
	this->totalRideUnride_Time =  totalRideUnride_Time;
	this->cost = cost;
	Execute();
}


ReadyEvent::ReadyEvent(Company* pComp) {
	this->pComp = pComp;
}

void ReadyEvent::Load(ifstream& File) {
	string PassengerType, EventTime, LT;

	File >> PassengerType >> EventTime >> this->ID >> this->Delivery_distance >> LT >> this->cost;

	if (PassengerType == "N") {
		this->Ptype = Passenger_Type::NP;
	}
	else if (PassengerType == "S") {
		this->Ptype = Passenger_Type::SP;
	}
	else {
		this->Ptype = Passenger_Type::VP;
	}
	int colonidx = 0;
	for (int j = 0; j < EventTime.size(); j++) {
		if (EventTime[j] == ':') {
			colonidx = j;
		}
	}
	int pDay = stoi(EventTime.substr(0, colonidx));
	int pHour = stoi(EventTime.substr(colonidx + 1, EventTime.size() - colonidx));
	this->EventTime = Time(pDay, pHour);
	this->totalRideUnride_Time = double(stoi(LT));
	this->Execute();
}


void ReadyEvent::Execute() // Creates passenger and adds it to passenger list
{
	pPass = new Passengers(Ptype,EventTime, ID, totalRideUnride_Time,
		Delivery_distance, cost);
	pComp->add_ready(pPass);
}
