#pragma once
#include "Event.h"
class Company;
class ReadyEvent :
    public Event
{
private:
    Company* pComp;
    // Passenger Parameters
    Passengers* pPass = nullptr;
    Passenger_Type Ptype;
    double Ready_day, Ready_hour;
    int ID;
    double  Delivery_distance;
    double Ride_hour, UnRide_hour;
    double cost;

public:
    ReadyEvent(Company*,Passenger_Type,int,int,int,double, double, double);
    void Execute();
};

