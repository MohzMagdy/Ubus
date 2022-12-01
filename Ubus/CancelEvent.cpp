#include "CancelEvent.h"

CancelEvent::CancelEvent(Company* pComp)
{
	this->pComp = pComp;
	Execute();
}

void CancelEvent::Execute()
{
	// TEMPORARY: ID should be loaded from file
	cout << "Enter ID: ";
	cin >> this->ID;

	pPass = pComp->find_passenger(ID);
	if (pPass == nullptr)
	{
		cout << "No passenger with this ID" << endl;
	}
	else
	{
		// TEMPORARY: Should check if passenger is not riding before canceling
		pComp->delete_passenger(pPass);
	}
}