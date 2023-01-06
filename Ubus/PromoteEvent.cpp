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
	Passengers* pPass = pComp->pWaitNorm_find(ID);
	if (pPass == nullptr)
	{
		cout << "No Waiting Normal passenger with this ID" << endl;
	}
	else 
	{
		cout << "Passenger With ID " << pPass->Get_ID() << " is VIP Now" << endl;
		pPass->Set_passanger_type(Passenger_Type::VP);
		pComp->promoteNorm(pPass);
	}
}