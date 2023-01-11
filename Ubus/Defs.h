#pragma once
#include<iostream>

enum Event_Type
{
	Ready,
	Cancel,
	Promote
};

enum  Passenger_Type{
	NP,	// Normal Passenger Type
	SP,	// Special Passenger Type
	VP	// VIP Passenger Type
};

enum Bus_Type {
	NB,	// Normal Bus
	SB,	// Special Bus
	VB	// VIP Bus
};

enum Mode {
	Interactive,
	Step,
	Silent,
	Immediate
};
