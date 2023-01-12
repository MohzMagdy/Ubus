#include "PromoteEvent.h"
#include "Defs.h"
#include "Company.h"

PromoteEvent::PromoteEvent(Company* pComp,int ID,Time EventTime, int ExtraMoney)
{
	this->ExecuteTime = EventTime;
	this->ID = ID;
	this->pComp = pComp;
	this->ExtraMoney = ExtraMoney;
}

PromoteEvent::PromoteEvent(Company* pComp) {
	this->pComp = pComp;
}

Event_Type PromoteEvent::GetType() {
	return Event_Type::Promote;
}

void PromoteEvent::Load(ifstream& File) {
	string EventTime;
	File >> EventTime >> this->ID >> this->ExtraMoney;
	int colonidx = 0;
	for (int j = 0; j < EventTime.size(); j++) {
		if (EventTime[j] == ':') {
			colonidx = j;
		}
	}
	int pDay = stoi(EventTime.substr(0, colonidx));
	int pHour = stoi(EventTime.substr(colonidx + 1, EventTime.size() - colonidx));
	this->ExecuteTime = Time(pDay, pHour);
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