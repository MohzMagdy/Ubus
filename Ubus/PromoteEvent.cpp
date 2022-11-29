#include "PromoteEvent.h"
#include "Defs.h"

PromoteEvent::PromoteEvent(Company* pComp)
{
	this->pComp = pComp;
	Execute();
}

void PromoteEvent::Execute()
{
	// TEMPORARY: ID should be loaded from file
	cout << "Enter ID: ";
	cin >> this->ID;

	// Find user with ID
	Passengers* pPass = pComp->find_passenger(ID);
	if (pPass == nullptr)
	{
		cout << "No passenger with this ID" << endl;
	}
	else {
		if (pPass->get_passanger_type() == Passenger_Type::VP)
		{
			cout << "Passenger is already VIP" << endl;
		}
		else
		{
			pPass->Set_passanger_type(Passenger_Type::VP);
		}
	}
}