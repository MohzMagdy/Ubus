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
    // Passenger Parametersp
    Passengers* pPass = nullptr;
    Passenger_Type Ptype;
    int ID;
    double  Delivery_distance;
    double totalRideUnride_Time;
    double cost;

public:
    ReadyEvent(Company*);
    ReadyEvent(Company*,Passenger_Type,Time,int,double, double, double);
    void Execute();
    void Load(std::ifstream&);
    Event_Type GetType();
    Passenger_Type GetReadyPassengerType();
};

