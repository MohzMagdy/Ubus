#pragma once
#include "Event.h"
#include <sstream>
#include <fstream>

class Company;
class CancelEvent :
    public Event
{
private:
    Company* pComp = nullptr;
    int ID;

public:
    CancelEvent(Company*);
    CancelEvent(Company*,int,Time);
    void Execute();
    void Load(std::ifstream&);
    Event_Type GetType();
};

