#pragma once
#include "Event.h"
#include "Company.h"
class PromoteEvent :
    public Event
{
private:
    Company* pComp = nullptr;
    int ID;

public:
    PromoteEvent(Company*);
    void Execute();
};

