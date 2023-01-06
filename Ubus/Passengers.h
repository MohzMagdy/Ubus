#pragma once
#include"Defs.h"
#include"Time.h"
#include<iostream>
class Passengers {
private:
	Passenger_Type Ptype;
	Time Ready_Time; 
	int ID;
	Time Ride_Time;
	Time UnRide_Time;
	double  Delivery_distance;
	double cost;
public:
	Passengers();// no parameter constructor 
	Passengers(Passenger_Type Ptype, Time Ready_Time, int ID, Time Ride_Time, 
		Time UnRide_Time, double  Delivery_distance, double cost);//  constructor with parameter 
	/// parmeters geters 
	Passenger_Type get_passanger_type();
	Time Get_ready_Time();
	int Get_ID();
	Time Get_Ride_Time();
	Time Get_UnRide_Time();
	double Get_Delivery_distance();
	double Get_Cost();
	/// parmeters seters
	void Set_passanger_type(Passenger_Type pT);
	void Set_readytime(Time t);
	void Set_id(int id);
	void Set_Ride_Time(Time rH);
	void Set_UnRide_Time(Time unrH);
	void Set_Delivery_distance(double Deldist);
	void Set_Cost(double costt);
};