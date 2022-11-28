#pragma once
#include "Event.h"
#include "Company.h"
class ReadyEvent :
    public Event
{
private:
    Company* pComp = nullptr;
public:
    ReadyEvent(Company*);
    void getParameters();
    void Execute();
};

