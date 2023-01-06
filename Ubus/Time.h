#pragma once
#include<iostream>
#include<string.h>
class Time
{
private :
	int days;
	int hours;
public:
	Time(); // no parameter constructor 
	Time(int days, int hours); // parameter constructor
	Time(int h); // constructor with time parameter
	int Getdays(); // geter for day time
	int Gethours();// geter for time hour
	int Gettotalhours(); // geter for total time in hour
	void Setdays(int D); // seter for the day
	void Sethours(int H); // setter for the hours 
	Time operator-(Time anothertime); // funcation oveload the subtract the time 
	Time operator+(Time anothertime);// funcation oveload the add the time 
	Time operator-(int H_Sub); // funcation oveload the subtract the time by time in hour as input parmeter 
	Time operator+(int H_added);// funcation oveload the added the time by time in hour as input parmeter
	bool operator>(Time  anothertime);// funcation oveload the compare the time by another time -biger than-
	bool operator>=(Time  anothertime);// funcation oveload the compare the time by another time -biger than or equal-
	bool operator<(Time  anothertime);// funcation oveload the compare the time by another time -smaller than -
	bool operator<=(Time  anothertime);// funcation oveload the compare the time by another time -smaller than or equal-
	bool operator==(Time  anothertime);// funcation oveload the compare the time by another time -equal-
	bool operator!=(Time  anothertime);// funcation oveload the compare the time by another time -not equal-
	void PrintTime() const;// funcation oveload the print the time-
};

