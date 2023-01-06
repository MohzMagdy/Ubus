#include <iostream>
#include "priority_queue.h"
#include "LinkedList.h"
#include "Company.h"
#include "ReadyEvent.h"
#include "CancelEvent.h"
#include "PromoteEvent.h"
#include "Defs.h"

using namespace std;

int main()
{
	Company* pComp = new Company;

	bool exit = false;
	while (!exit)
	{

	}

	delete pComp;

}


/// this a test for time class you can test it by youself guys<3

//#include"Time.h"
//#include<iostream>
//using namespace std;
//int main() {
//	Time h(1, 20); Time v; Time H(48);
//	cout<<h.Getdays()<<endl;
//	cout<<h.Gethours() << endl;
//	h.PrintTime();
//	v.Setdays(1);
//	v.Sethours(23);
//	v.PrintTime();
//	H.PrintTime();
//	h.operator+(v).PrintTime();
//	h.operator-(v).PrintTime();
//	h.operator+(25).PrintTime();
//	h.operator-(4).PrintTime();
//}