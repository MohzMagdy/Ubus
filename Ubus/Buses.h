#pragma once
#include"Defs.h"
#include"Time.h"
#include "queue.h"
#include "Passengers.h"
#include"priority_queue.h"

class Buses {
private :
	Bus_Type bType;
	int BC;
	Time Checkup_time_HS;
	double Bus_speed; 
	Time DI;
	queue<Passengers*> passineside;
	int currentaboarding =0;
	priority_queue<Passengers*> pPass;
	priority_queue<Passengers*> seats;
	int onboardCount = 0;
	int no_journeys = 0;
	int inmaintinancetime = 0;
public:
	Buses();// no parameter constructor 
	Buses(Bus_Type bType, int BC, Time Checkup_time_HS, double Bus_speed, Time DI, int currentaboarding);// constructor with parameters
	/// parmeters getters 
	Bus_Type get_bus_type();
	int get_bus_capacity();
	Time get_Check_point();
	double get_bus_speed();
	Time get_Delivery_interval();
	int get_onboardCount();
	/// parmeters setters 
	void Set_bus_type(Bus_Type BT);
	void Set_bus_capacity(int BCC);
	void Set_Check_point(Time cH);
	void Set_bus_speed(double BS);
	void  set_Delivery_interval(Time DIN);
	void passenger_aboard(Passengers* rider);
	void passenger_peek(Passengers* &ridertopeek);
	void passenger_Deqeue(Passengers* ridertodeque);

	bool isfull();

	void board(Passengers* pPass);
	void increase_journey();
	int get_journeys();
	void set_journey(int x);
	void increase_maintinancetime();
	int get_maintitnance_time();
};