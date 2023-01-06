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

	pPass = pComp->pWaitNorm_find(ID);
	if (pPass == nullptr)
	{
		cout << "No waiting normal passenger with this ID" << endl;
	}
	else
	{
		cout << "Passenger with ID: " << pPass->Get_ID() << " is Cancelled" << endl;
		pComp->pWaitNorm_delete(pPass);
	}
}