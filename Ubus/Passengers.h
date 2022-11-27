#pragma once
#include"Defs.h"

#include<iostream>
class Passengers {
private: 
	double Ready_day, Ready_hour; // this type will be drivan from class of time that will be drivan from simulation file
	double Ride_hour, UnRide_hour;// this type will be drivan from class of time // this type will be drivan from class of time 
	Passenger_Type Ptype;
	double  Delivery_distance;
	double cost;
public :
	Passengers(double Ready_day, double Ready_hour, double Ride_hour, double UnRide_hour, 
		Passenger_Type Ptype, double  Delivery_distance, double cost) {
		this->Ready_day = Ready_day;
		this->Ready_hour = Ready_hour;
		this->Ride_hour = Ride_hour;
		this->UnRide_hour = UnRide_hour;
		this->Ptype = Ptype;
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
	void Set_Unride_Hour(double UrH){
		UnRide_hour = UrH;
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
	double get_Unride_Hour() {
		return UnRide_hour;
	}
	Passenger_Type  get_passanger_type() {
		return Ptype;
	}
	double get_Delivery_distance() {
		return Delivery_distance;
	}
	double get_Cost() {
		return cost;
	}
};