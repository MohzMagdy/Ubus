#include <iostream>
#include "priority_queue.h"
#include "LinkedList.h"
#include "Company.h"
#include "ReadyEvent.h"
#include "CancelEvent.h"
#include "PromoteEvent.h"
#include "Defs.h"

using namespace std;

int main()
{
	Company* pComp = new Company;

	// Pick Event Type
	cout << "Enter Event type: (0. Ready, 1. Cancel, 2. Promote): ";
	int eType;
	cin >> eType;

	Event* pEvent = nullptr;
	switch (eType) // Defines Event Type based on Selection
	{
	case Ready:
		pEvent = new ReadyEvent(pComp);
		break;
	case Cancel:
		pEvent = new CancelEvent(pComp);
		break;
	case Promote:
		pEvent = new PromoteEvent(pComp);
		break;
	}
	pEvent->Execute();
	pComp->add_event(pEvent);

}