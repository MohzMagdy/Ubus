#pragma once
#include"Defs.h"

#include<iostream>
class Passengers {
private: 
	Passenger_Type Ptype;
	double Ready_day, Ready_hour; // this type will be drivan from class of time that will be drivan from simulation file
	int ID;
	double Ride_hour;// this type will be drivan from class of time // this type will be drivan from class of time 
	double  Delivery_distance;
	double cost;
public:
	Passengers(Passenger_Type Ptype, double Ready_day, double Ready_hour, int ID,
		double Ride_hour, double  Delivery_distance, double cost) {
		this->Ptype = Ptype;
		this->Ready_day = Ready_day;
		this->Ready_hour = Ready_hour;
		this->ID = ID;
		this->Ride_hour = Ride_hour;
		this->Delivery_distance = Delivery_distance;
		this->cost = cost;
	}
	/// seters
	void Set_readytime(double RD, double RH) {
		Ready_day = RD;
		Ready_hour = RH;
	}
	void Set_Ride_houre( double rH){
		Ride_hour = rH;
	}
	void Set_passanger_type(Passenger_Type pT) {
		Ptype = pT;
	}
	void Set_Delivery_distance(double Deldist) {
		Delivery_distance = Deldist;
	}
	void Set_Cost( double costt){
		cost = costt;
	}
	/// getters 
	double get_readyday() {
		return Ready_day;
	}
	double get_readyhour() {
		return Ready_hour;
	}

	double get_Ride_houre() {
		return Ride_hour;
	}
	Passenger_Type get_passanger_type() {
		return Ptype;
	}
	double get_Delivery_distance() {
		return Delivery_distance;
	}
	double get_Cost() {
		return cost;
	}
	int get_ID() {
		return ID;
	}
};