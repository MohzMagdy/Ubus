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

	Passengers* pPass = pComp->find_passenger(ID);
	if (pPass == nullptr)
	{
		cout << "No passenger with this ID" << endl;
	}
	else
	{
		// TEMPORARY: Should check if passenger is not riding before canceling
		// Deleting passenger by going over the queue and dequeuing the found passenger without enqueuing it back
		bool found = false;
		int passenger_count = pComp->get_passenger_count();
		Passengers* pHelper;

		for (int i = 0; i < passenger_count; i++) // Loop goes over whole queue to keep the order unchanged
		{
			pHelper = pComp->Dequeue_passenger();
			if (!found && pHelper == pPass)
			{
				delete pHelper;
				found = true;
			}
			else
			{
				pComp->Enqueue_passenger(pHelper);
			}
		}
	}
}