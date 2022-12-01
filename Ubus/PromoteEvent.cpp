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
	this->pPass = pComp->find_passenger(ID);
	if (this->pPass == nullptr)
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