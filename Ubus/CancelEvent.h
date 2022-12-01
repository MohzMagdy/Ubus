#pragma once
#include "Event.h"
#include "Company.h"
class CancelEvent :
    public Event
{
private:
    Company* pComp = nullptr;

    int ID;

public:
    CancelEvent(Company*);
    void Execute();
};

