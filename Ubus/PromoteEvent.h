#pragma once
#include "Event.h"
#include <sstream>
#include <fstream>

class Company;
class PromoteEvent :
    public Event
{
private:
    Company* pComp = nullptr;
    int ID;
    int ExtraMoney;

public:
    PromoteEvent(Company*,int,Time,int);
    PromoteEvent(Company*);
    void Execute();
    void Load(std::ifstream&);
    Event_Type GetType();
};

