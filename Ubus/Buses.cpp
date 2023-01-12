#include"Buses.h"
#include"Defs.h"

Buses::Buses() 
{
	bType = NB;
	BC = 0;
	Checkup_time_HS.Setdays(0); Checkup_time_HS.Sethours(0);
	Bus_speed = 0;
	DI.Setdays(0); DI.Sethours(0);
	currentaboarding = 0;
}
	Buses::Buses(Bus_Type bType, int BC, Time Checkup_time_HS, double Bus_speed, Time DI, int currentaboarding, int ID) {
		this->bType = bType;
		this->BC = BC;
		this->Checkup_time_HS = Checkup_time_HS;
		this->Bus_speed = Bus_speed;
		this->DI = DI;
		this->currentaboarding = currentaboarding;
		this->ID = ID;
	}

Bus_Type Buses:: get_bus_type() {return bType;}
int Buses::get_bus_capacity() {return BC;}
Time Buses::get_Check_point() {return Checkup_time_HS;}		
int Buses::getID() { return ID; }
double Buses::get_bus_speed() {return Bus_speed;}
priority_queue<Passengers*> Buses::getSeats() { return seats; }
Time Buses::get_Delivery_interval() {return DI;}
void Buses::Set_Start_Moving_Time(Time t) { StartMovingTime = t; };
void Buses::Set_bus_type(Bus_Type BT) {bType = BT;}
void Buses::Set_bus_capacity(int BCC) {BC = BCC;}
void Buses::Set_Check_point(Time cH) {Checkup_time_HS = cH;}
void Buses::Set_bus_speed(double BS) {Bus_speed = BS;}
void Buses::set_Delivery_interval(Time DIN) {DI = DIN;}

	void Buses::passenger_aboard(Passengers* rider)
	{
		if (currentaboarding <= BC)
		{
			passineside.Enqueue(rider);
		}
		else
		{
			cout << "unable to aboard" << endl;
		}
		currentaboarding++;
	}

	void Buses::passenger_peek(Passengers* &ridertopeek)	
	{	this->seats.Peek(ridertopeek);}

	void Buses::passenger_Deqeue(Passengers* ridertodeque)
	{
		ridertodeque = seats.Dequeue();
		
		if (ridertodeque != nullptr) { onboardCount--; }
	}

	bool Buses::isfull()
	{
		bool x = false;
		if (onboardCount>=BC)
		{
			x = true;
			return true;
		}
		return x;
	}
int Buses::get_onboardCount()
{
	
	return onboardCount;
}

void Buses::board(Passengers* pPass)
{
		seats.Enqueue(pPass, -(pPass->Get_Delivery_distance()));
		onboardCount++;
}

void Buses::increase_journey()
{
	no_journeys++;
}

int Buses::get_journeys()
{
	return no_journeys;
}

void Buses::set_journey(int x)
{
	no_journeys = x;
}

void Buses::increase_maintinancetime()
{
	inmaintinancetime++;
}

int Buses::get_maintitnance_time()
{
	return inmaintinancetime;
}

priority_queue<Passengers*>* Buses::get_seats()
{
	return &seats;
}
