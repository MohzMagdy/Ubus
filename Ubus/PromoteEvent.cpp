#include "PromoteEvent.h"

PromoteEvent::PromoteEvent(Company* pComp)
{
	this->pComp = pComp;
}

void PromoteEvent::getParameters()
{
}

void PromoteEvent::Execute()
{
	getParameters();
}