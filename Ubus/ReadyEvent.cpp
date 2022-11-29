#include "ReadyEvent.h"

ReadyEvent::ReadyEvent(Company* pComp)
{
	this->pComp = pComp;
	ID = pComp->get_passenger_count() + 1;
	Execute();
}

void ReadyEvent::getParameters() // TEMPORARY: Should get parameters from load function
{
	cout << "Enter Passenger Parameters (Type, Ready day and hour, Ride and unride hour, Distance, cost):" << endl;
	int PtypeNum;
	cin >>
		PtypeNum >>
		this->Ready_day >>
		this->Ready_hour >>
		this->Ride_hour >>
		this->UnRide_hour >>
		this->Delivery_distance >>
		this->cost;

	Ptype = Passenger_Type(PtypeNum);
}

void ReadyEvent::Execute() // Creates passenger and adds it to passenger list
{
	getParameters();
	pPass = new Passengers(Ptype, Ready_day, Ready_hour, Ride_hour, ID, 
		UnRide_hour,Delivery_distance, cost);
	pComp->add_passenger(pPass);
}
