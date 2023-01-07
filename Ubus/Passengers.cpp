#include"Passengers.h"
#include"Defs.h"

Passengers::Passengers()
{
	Ptype = NP;
	Ready_Time.Setdays(0); Ready_Time.Sethours(0);
	ID=0;
	Ride_Time.Setdays(0); Ride_Time.Sethours(0);
	UnRide_Time.Setdays(0); UnRide_Time.Sethours(0);
	Delivery_distance=0;
	cost = 0;
	MaxW = 0;
}
Passengers::Passengers(Passenger_Type Ptype, Time Ready_Time, int ID, Time Ride_Time, double Delivery_distance, double cost)
{
	this->Ptype = Ptype;
	this->Ready_Time = Ready_Time;
	this->ID= ID;
	this ->Ride_Time = Ride_Time;
	this -> Delivery_distance = Delivery_distance;
	this-> cost = cost;
	this->MaxW = MaxW;
}

Passenger_Type Passengers::get_passanger_type(){return Ptype;}
Time Passengers::Get_ready_Time(){return Ready_Time;}
int Passengers::Get_ID(){return ID;}
Time Passengers::Get_Ride_Time(){return Ride_Time;}
Time Passengers::Get_UnRide_Time(){return UnRide_Time;}
double Passengers::Get_Delivery_distance(){return Delivery_distance;}
double Passengers::Get_Cost(){return cost;}

Time Passengers::Get_MaxW()
{
	return MaxW;
}

void Passengers::Set_passanger_type(Passenger_Type pT){this->Ptype = pT;}
void Passengers::Set_readytime(Time t){this->Ready_Time = t;}
void Passengers::Set_id(int id){this->ID = id;}
void Passengers::Set_Ride_Time(Time rH){this->Ride_Time = rH;}
void Passengers::Set_UnRide_Time(Time unrH){this->UnRide_Time = unrH;}
void Passengers::Set_Delivery_distance(double Deldist){this->Delivery_distance = Deldist;}
void Passengers::Set_Cost(double costt){this->cost = costt;}

void Passengers::Set_MaxW(int x, int y)
{
	MaxW.Setdays(x);
	MaxW.Sethours(y);
}
