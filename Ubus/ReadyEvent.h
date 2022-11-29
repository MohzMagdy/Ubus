#pragma once
#include "Event.h"
#include "Company.h"
class ReadyEvent :
    public Event
{
private:
    Company* pComp = nullptr;

    // Passenger Parameters
    Passengers* pPass = nullptr;

    Passenger_Type Ptype;
    double Ready_day, Ready_hour;
    int ID;
    double  Delivery_distance;
    double Ride_hour, UnRide_hour;
    double cost;

public:
    ReadyEvent(Company*);
    void getParameters();
    void Execute();
};

