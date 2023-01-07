#pragma once
#include "Event.h"
#include <sstream>
#include <fstream>

class Company;
class ReadyEvent :
    public Event
{
private:
    Company* pComp;
    Time EventTime;
    // Passenger Parametersp
    Passengers* pPass = nullptr;
    Passenger_Type Ptype;
    int ID;
    double  Delivery_distance;
    Time Ride_Hour;
    double cost;

public:
    ReadyEvent(Company*);
    ReadyEvent(Company*,Passenger_Type,Time,int,double, Time, double);
    void Execute();
    void Load(std::ifstream&);
};

