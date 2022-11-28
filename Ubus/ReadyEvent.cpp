#include "ReadyEvent.h"

ReadyEvent::ReadyEvent(Company* pComp)
{
	this->pComp = pComp;
}

void ReadyEvent::getParameters()
{}

void ReadyEvent::Execute()
{
	Passengers* pPass = new Passengers();
	pComp->add_passenger(pPass);
}
