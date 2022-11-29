#include "CancelEvent.h"

CancelEvent::CancelEvent(Company* pComp)
{
	this->pComp = pComp;
	Execute();
}

void CancelEvent::Execute()
{
}