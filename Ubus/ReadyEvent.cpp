#include "ReadyEvent.h"
#include "Company.h"
ReadyEvent::ReadyEvent(Company* pComp,Passenger_Type pType,int Ready_day, int readyHour, int ID, double distance, double ridehour, double cost)
{
	this->pComp = pComp;
	this->Ptype = pType;
	this->Ready_day = Ready_day;
	this->Ready_hour = readyHour;
	this->ID = ID;
	this->Delivery_distance = distance;
	this->Ride_hour = ridehour;
	this->cost = cost;
	Execute();
}


void ReadyEvent::Execute() // Creates passenger and adds it to passenger list
{
	pPass = new Passengers(Ptype, Ready_day, Ready_hour, ID, Ride_hour,
		Delivery_distance, cost);
	pComp->add_passenger(pPass);
}
