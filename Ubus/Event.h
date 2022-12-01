#pragma once
#include "Buses.h"
#include "Passengers.h"

class Event
{
protected:
	Passengers* pPass = nullptr;

public:
	Event() {};
	virtual void Execute() = 0;
	Passengers* get_pPass()
	{
		return pPass;
	}
	void set_pPass(Passengers* pPass)
	{
		this->pPass = pPass;
	}
};

