#include "Time.h"

Time::Time() {days = 0; hours = 0 ;}
Time::Time(int days, int hours)
{
	if (days < 0 || (hours < 0 || hours >= 24)) 
	{
		if (days < 0){ std::cout << "Value Error: " << "Days cannot be negative" << std::endl;}
		else if ((hours < 0 || hours >= 24)) { std::cout << "Value Error: " << "Invalid Hour" << std::endl;}
		 exit(1);
	}
	else { this->days = days; this->hours = hours; }
}
Time::Time(int h)
{
	if (h < 0) { std::cout << "Value Error: " << "Hours Number cannot be negative!" << std::endl; exit(1); }
	else {
		this->hours = h % 24;
		this->days = (h - (h % 24)) / 24;
	}
}


int Time::Getdays() { return this->days; }
int Time::Gethours() { return this->hours;}
int Time::Gettotalhours() { return (this->days * 24 + this->hours); }


void Time::Setdays(int D)
{
	if (D < 0){ std::cout << "Value Error: " << "Days cannot be negative" << std::endl; exit(1);}
	else { this->days = D; }
}
void Time::Sethours(int H)
{
	if (H < 0 || H >= 24) { std::cout << "Value Error: " << "Invalid Hour" << std::endl; exit(1); }
	else {this->hours = H ;}
}


Time Time::operator-(Time anothertime)
{
	if ((this->days < anothertime.days) || (this->days == anothertime.days && this->hours < anothertime.hours)) 
	{std::cout << "Value Error: " << "Invalid operands!" << std::endl; exit(1);}
	else
	{
		int newdays, newhours;
		if (this->hours < anothertime.hours) 
		{
			newdays = this->days - anothertime.days;
			newhours = 24 - (anothertime.hours - this->hours);
		}
		else
		{
			newdays = this->days - anothertime.days;
			newhours = this->hours - anothertime.hours ;
		}
		return Time(newdays, newhours);
	}
}

Time Time::operator+(Time anothertime)
{
	int newdays, newhours;
	if (this->hours + anothertime.hours >= 24)
	{
		newdays = this->days + anothertime.days + 1 ;
		newhours = (anothertime.hours + this->hours) - 24;
	}
	else
	{
		newdays = this->days + anothertime.days;
		newhours = this->hours + anothertime.hours;
	}
	return Time(newdays, newhours);
}

Time Time::operator-(int H_Sub)
{
	int subtractedday = H_Sub / 24;
	H_Sub = H_Sub % 24;

	if ((this->days < subtractedday) || (this->days == subtractedday && this->hours < H_Sub))
	{
		std::cout << "Value Error: " << "Invalid operands!" << std::endl; exit(1);
	}
	else
	{
		int newdays, newhours;
		if (this->hours < H_Sub)
		{
			newdays = this->days - H_Sub;
			newhours = 24 - (H_Sub - this->hours);
		}
		else
		{
			newdays = this->days - H_Sub;
			newhours = this->hours - H_Sub;
		}
		return Time(newdays, newhours);
	}
}

Time Time::operator+(int H_added)
{
	int added_days = H_added / 24;
	H_added = H_added % 24;
	int newdays, newhours;
	if ((this->hours + H_added) >= 24)
	{
		newdays = this->days + added_days + 1;
		newhours = (H_added + this->hours) - 24;
	}
	else
	{
		newdays = this->days + added_days;
		newhours = this->hours + H_added;
	}
	return Time(newdays, newhours);
}

bool Time::operator>(Time anothertime){if ((Gettotalhours()) > (anothertime.days * 24 + anothertime.hours)) return true; else return false;}
bool Time::operator>=(Time anothertime){if ((Gettotalhours()) >= (anothertime.days * 24 + anothertime.hours)) return true;else return false;}
bool Time::operator<(Time anothertime){if ((Gettotalhours()) < (anothertime.days * 24 + anothertime.hours)) return true;else return false;}
bool Time::operator<=(Time anothertime){if ((Gettotalhours()) <= (anothertime.days * 24 + anothertime.hours)) return true;else return false;}
bool Time::operator==(Time anothertime){if ((Gettotalhours()) == (anothertime.days * 24 + anothertime.hours)) return true;else return false;}
bool Time::operator!=(Time anothertime){if ((Gettotalhours()) != (anothertime.days * 24 + anothertime.hours)) return true;else return false;}

void Time::PrintTime() const
{
	std::cout << this->days << ":" << this->hours << std::endl;
}