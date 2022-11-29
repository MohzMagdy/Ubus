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

	bool exit = false;
	while (!exit)
	{
		// Pick Event Type
		cout << "Enter Event type: (0. Ready, 1. Cancel, 2. Promote, Else: Exit): "; 
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
		default:
			exit = true;
			break;
		}
		pComp->add_event(pEvent);
	}

	delete pComp;
}