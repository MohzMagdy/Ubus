#include"Passengers.h"
#include"Defs.h"

Passengers::Passengers()
{
	Ptype = NP;
	Ready_Time.Setdays(0); Ready_Time.Sethours(0);
	ID=0;
	totalRideUnride_Time = 0;
	Delivery_distance=0;
	cost = 0;
	MaxW.Setdays(0);
	MaxW.Sethours(0);
}
Passengers::Passengers(Passenger_Type Ptype, Time Ready_Time, int ID, double totalRideUnride_Time, double Delivery_distance, double cost)
{
	this->Ptype = Ptype;
	this->Ready_Time = Ready_Time;
	this->ID= ID;
	this ->totalRideUnride_Time = totalRideUnride_Time;
	this -> Delivery_distance = Delivery_distance;
	this-> cost = cost;
	MaxW.Setdays(0); ///will be changed
	MaxW.Sethours(0); ///will be changed
}

Passenger_Type Passengers::get_passanger_type(){return Ptype;}
Time Passengers::Get_ready_Time(){return Ready_Time;}
int Passengers::Get_ID(){return ID;}
double Passengers::Get_totalRideUnride_Time(){return  totalRideUnride_Time;}
double Passengers::Get_Delivery_distance(){return Delivery_distance;}
double Passengers::Get_Cost(){return cost;}
Time Passengers::Get_waitTime() { return waitTime; }

double Passengers::Get_delvTime()
{
	return this->delvtime;
}

Time Passengers::Get_MaxW()
{
	return MaxW;
}

void Passengers::Set_passanger_type(Passenger_Type pT){this->Ptype = pT;}
void Passengers::Set_readytime(Time t){this->Ready_Time = t;}
void Passengers::Set_id(int id){this->ID = id;}
void Passengers::Set_totalRideUnride_Time(double t){this-> totalRideUnride_Time = t;}
void Passengers::Set_Delivery_distance(double Deldist){this->Delivery_distance = Deldist;}
void Passengers::Set_Cost(double costt){this->cost = costt;}
void Passengers::Set_delvtime(double delvtime) { this->delvtime = delvtime; }

void Passengers::Set_waitTime(Time boardingTime)
{
	this->waitTime = boardingTime - Ready_Time;
}

void Passengers::Set_MaxW(int x, int y)
{
	MaxW.Setdays(x);
	MaxW.Sethours(y);
}

void Passengers::increaseMaxwhr()
{
	MaxW=MaxW.operator+(1);
}


double Passengers::calcPriority()
{
	return (Ready_Time.Gettotalhours()*10 + Delivery_distance + cost);
}

void Passengers::setbuspasid(int x)
{
	passengersbusid = x;
}

int Passengers::getbuspasid()
{
	return passengersbusid;
}
