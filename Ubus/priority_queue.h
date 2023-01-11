#pragma once
#include "Node.h"
#include <iostream>

using namespace std;

template<typename T>
class priority_queue
{
private:
	Node<T>* Front;
	Node<T>* Rear;
	int c = 0;
public:
	priority_queue();
	void Enqueue(Node<T>* R);///inserts nodes according to its priority
	void Enqueue(T item);///inserts item according to its priority
	void Enqueue(T item, double pir);
	T Dequeue();///deque from the beginning
	bool isempty();///checks if queue is empty or not
	void printlist();///print queue data
	int getcounter();///get number of data in queue
	void Peek(T& data);/// get the front data without delete from the qeue
	Node<T>* ReturnFront();
};

template<typename T>
priority_queue<T>::priority_queue()
{
	Front = nullptr;
	Rear = nullptr;
}

template<typename T>
bool priority_queue<T>::isempty()
{
	if (Front == nullptr && Rear == nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<typename T>
void priority_queue<T>::Enqueue(Node<T>* R)
{
	Node<T>* NP = new Node<T>;
	NP->set_data(R->get_data());
	NP->set_priority(R->get_priority());
	if (isempty())
	{
		Front = Rear =  NP;
	}
	else
	{
		if (Rear->get_priority()>NP->get_priority())
		{
			Rear->set_next(NP);
			Rear = NP;
		}
		else
		{
			Node<T>* temp=Front;
			if (NP->get_priority()>=Front->get_priority())
			{
				NP->set_next(Front);
				Front = NP;
			}
			else
			{
				while (temp->get_priority() > NP->get_priority())
				{
					temp = temp->get_next();
				}
				temp->set_next(NP);
			}
			
		}
	}
	c++;
}

template<typename T>
void priority_queue<T>::Enqueue(T item, double pir)
{
	Node<T>* NP = new Node<T>(item);
	Enqueue(NP);
}

template<typename T>
void priority_queue<T>::Enqueue(T item)
{
	Node<T>* NP = new Node<T>(item);
	Enqueue(NP);
}

template<typename T>
T priority_queue<T>::Dequeue()
{
	if (isempty())
	{
		
		cout << "The queue is empty" << endl;
		c -= 1;
		return NULL;

	}
	else if (Front == Rear)
	{
		T valueF = Front->get_data();
		Front = Rear = nullptr;
		c -= 1;
		return valueF;
	}
	else
	{
		Node<T>* helper = Front;
		T valueF = Front->get_data();
		Front = Front->get_next();
		c -= 1;
		return valueF;
	}

}

template<typename T>
void priority_queue<T>::printlist()
{
	Node<T>* temp = Front;
	while (temp != nullptr)
	{
		cout << temp->get_data() << " ";
		temp = temp->get_next();
	}
	cout << endl;
}
template<typename T>
int priority_queue<T>::getcounter() {
	return c;
}

template<typename T>
void priority_queue<T>::Peek(T& data)
{
	if (isempty()) {
		data = nullptr;
		return;
	}
	data = Front->get_data();
}

template<typename T>
inline Node<T>* priority_queue<T>::ReturnFront()
{
	return Front;
}

