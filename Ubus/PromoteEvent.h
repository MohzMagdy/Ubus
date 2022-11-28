#pragma once
#include "Event.h"
#include "Company.h"
class PromoteEvent :
    public Event
{
private:
    Company* pComp = nullptr;
public:
    PromoteEvent(Company*);
    void getParameters();
    void Execute();
};

