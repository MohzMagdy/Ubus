#include "CancelEvent.h"
#include "Company.h"

CancelEvent::CancelEvent(Company* pComp,int ID,Time EventTime)
{
	this->ExecuteTime = EventTime;
	this->pComp = pComp;
	this->ID = ID;
}


CancelEvent::CancelEvent(Company* pComp) {
	this->pComp = pComp;
}

void CancelEvent::Load(ifstream& File) {
	string EventTime;
	File >> EventTime >> this->ID;
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

Event_Type CancelEvent::GetType() {
	return Event_Type::Cancel;
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
		pComp->pWaitNorm_delete(pPass);
	}
}