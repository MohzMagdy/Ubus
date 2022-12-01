#include "PromoteEvent.h"
#include "Defs.h"
#include "Company.h"

PromoteEvent::PromoteEvent(Company* pComp,int ID)
{
	this->ID = ID;
	this->pComp = pComp;
	Execute();
}

void PromoteEvent::Execute()
{
	Passengers* pPass = pComp->find_passenger(ID);
	if (pPass == nullptr)
	{
		cout << "No passenger with this ID" << endl;
	}
	else {
		if (this->pPass->get_passanger_type() == Passenger_Type::VP)
		{
			cout << "Passenger is already VIP" << endl;
		}
		else
		{
			this->pPass->Set_passanger_type(Passenger_Type::VP);
		}
	}
}