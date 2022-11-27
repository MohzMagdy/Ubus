#pragma once
#include"Defs.h"
class Buses {
private :
	Bus_Type bType;
	int BC;
	double Checkup_time_HS; /// time class 
	double Bus_speed; 
	double DI; /// time classs
	
	Buses(Bus_Type bType,int BC,double Checkup_time_HS,double Bus_speed , double DI) {
		this->bType = bType;
		this->BC = BC;
		this->Checkup_time_HS = Checkup_time_HS;
		this->Bus_speed = Bus_speed;
		this->DI = DI;
	}


	///sstters
	void Set_bus_type(Bus_Type BT) {
		bType = BT;
	}
	void Set_bus_capacity(int BCC) {
		BC = BCC;
	}
	void Set_Check_point(double cH) {
		Checkup_time_HS = cH;
	 }
	void Set_bus_speed(double BS) {
		Bus_speed = BS;
	}
	void  set_Delivery_interval(double DIN) {
		DI = DIN;
	}


	///getters
	Bus_Type get_bus_type() {
		return bType;
	}
	int get_bus_capacity() {
		return BC;
	}
	double get_Check_point() {
		return Checkup_time_HS;
	}
	double get_bus_speed() {
		return Bus_speed;
	}
	double  get_Delivery_interval() {
		return DI;
	}

};