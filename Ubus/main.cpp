#include <iostream>
#include "LinkedList.h"
#include"priority_queue.h"
#include"Node.h"
#include"queue.h"
using namespace std;

int main()
{
	priority_queue<int> pq;
	Node<int>l(9);
	Node<int>k(5);
	Node<int>j(1);
	l.set_priority(1);
	k.set_priority(5);
	j.set_priority(2);
	pq.Enqueue(&l);
	pq.Enqueue(&k);
	pq.Enqueue(&j);
	pq.printlist();
	cout << pq.getcounter()<<endl;
	pq.Dequeue();
	pq.printlist();
	cout << pq.getcounter()<<endl;
}