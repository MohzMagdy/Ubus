#pragma once
#include "Event.h"
class Company;
class CancelEvent :
    public Event
{
private:
    Company* pComp = nullptr;

    int ID;

public:
    CancelEvent(Company*,int);
    void Execute();
};

