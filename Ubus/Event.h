#pragma once
#include "Buses.h"
#include "Passengers.h"
#include <fstream>
#include <sstream>




class Event
{
protected:
	Passengers* pPass = nullptr;
	Time ExecuteTime;
public:
	Event() {};
	virtual void Execute() = 0;
	virtual void Load(std::ifstream&) = 0;
	virtual Event_Type GetType() = 0;
	virtual Passenger_Type GetReadyPassengerType() {
		return Passenger_Type::NP;
	};


	Passengers* get_pPass()
	{
		return pPass;
	}
	void set_pPass(Passengers* pPass)
	{
		this->pPass = pPass;
	}
	Time getEventTime() {
		return ExecuteTime;
	}

	
};

