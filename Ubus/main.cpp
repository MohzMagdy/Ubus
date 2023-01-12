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
//int main()
//{
//	Node<int>* test1 = new Node<int>(1);
//	test1->set_priority(5);
//
//	Node<int>* test2 = new Node<int>(2);
//	test2->set_priority(10);
//	
//
//	Node<int>* test3 = new Node<int>(3);
//	test3->set_priority(1);
//	
//
//	priority_queue<int> prque;
//	prque.Enqueue(test1);
//	prque.Enqueue(test2);
//	prque.Enqueue(test3);
//	prque.printlist();
//	
//	prque.ReturnFront()->set_priority(50);
//	prque.printlist();
//	priority_queue<int> testqueue;
//	prque.Enqueue(prque.Dequeue());
//	prque.Enqueue(prque.Dequeue());
//	prque.Enqueue(prque.Dequeue());
//	testqueue.printlist();
//}