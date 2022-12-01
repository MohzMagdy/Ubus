#include "CancelEvent.h"
#include "Company.h"

CancelEvent::CancelEvent(Company* pComp,int ID)
{
	this->pComp = pComp;
	this->ID = ID;
	Execute();
}

void CancelEvent::Execute()
{

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