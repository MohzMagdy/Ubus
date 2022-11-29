#pragma once
#include<iostream>

enum Event_Type
{
	Ready,
	Cancel,
	Promote
};

enum class Passenger_Type{
	NP,	// Normal Passenger Type
	SP,	// Special Passenger Type
	VP	// VIP Passenger Type
};

enum class Bus_Type {
	NB,	// Normal Bus
	SB,	// Special Bus
	VB	// VIP Bus
};
