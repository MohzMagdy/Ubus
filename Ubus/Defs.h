#pragma once
#include<iostream>

enum Event_Type
{
	Ready,
	Cancel,
	Promote
};

enum class Passenger_Type{
	N,	// Normal Passenger Type
	S,	// Special Passenger Type
	V	// VIP Passenger Type
};

enum class Bus_Type {
	NB,	// Normal Bus
	SB,	// Special Bus
	VB	// VIP Bus
};
