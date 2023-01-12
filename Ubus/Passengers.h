#pragma once
#include"Defs.h"
#include"Time.h"
#include<iostream>
class Passengers {
private:
	Passenger_Type Ptype;
	Time Ready_Time; 
	int ID;
	double totalRideUnride_Time;
	double  Delivery_distance;
	double cost;
	Time MaxW;
	Time waitTime;
	double delvtime;
	int passengersbusid;
public:
	Passengers();// no parameter constructor 
	Passengers(Passenger_Type Ptype, Time Ready_Time, int ID, double totalRideUnride_Time, double  Delivery_distance, double cost);//  constructor with parameter 
	/// parmeters geters 
	Passenger_Type get_passanger_type();
	Time Get_ready_Time();
	int Get_ID();
	double Get_totalRideUnride_Time();
	double Get_Delivery_distance();
	double Get_Cost();
	Time Get_MaxW();
	Time Get_waitTime();
	double Get_delvTime();
	/// parmeters seters
	void Set_passanger_type(Passenger_Type pT);
	void Set_readytime(Time t);
	void Set_id(int id);
	void Set_totalRideUnride_Time(double t);
	void Set_Delivery_distance(double Deldist);
	void Set_Cost(double costt);
	void Set_MaxW(int x, int y);
	void increaseMaxwhr();
	void Set_waitTime(Time boardingTime);
	void Set_delvtime(double delvtime);

	double calcPriority();
	void setbuspasid(int x);
	int getbuspasid();
};