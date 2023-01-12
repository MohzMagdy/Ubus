#include "ReadyEvent.h"
#include "Company.h"
#include <stdio.h>
#include <string.h>

ReadyEvent::ReadyEvent(Company* pComp,Passenger_Type pType,Time EventTime, int ID, double distance, double totalRideUnride_Time, double cost)
{
	this->pComp = pComp;
	this->Ptype = pType;
	this->ID = ID;
	this->ExecuteTime = EventTime;
	this->Delivery_distance = distance;
	this->totalRideUnride_Time =  totalRideUnride_Time;
	this->cost = cost;
}



Passenger_Type ReadyEvent::GetReadyPassengerType() {
	return Ptype;
}


ReadyEvent::ReadyEvent(Company* pComp) {
	this->pComp = pComp;
}

Event_Type ReadyEvent::GetType() {
	return Event_Type::Ready;
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
	this->ExecuteTime = Time(pDay, pHour);
	this->totalRideUnride_Time = double(stoi(LT));
}


void ReadyEvent::Execute() // Creates passenger and adds it to passenger list
{
	pPass = new Passengers(Ptype, ExecuteTime, ID, totalRideUnride_Time,
		Delivery_distance, cost);
	pComp->add_ready(pPass);
}
