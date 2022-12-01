#pragma once
#include "Event.h"
class Company;
class PromoteEvent :
    public Event
{
private:
    Company* pComp = nullptr;
    int ID;

public:
    PromoteEvent(Company*,int);
    void Execute();
};

