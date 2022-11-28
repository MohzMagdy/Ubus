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
	void Enqueue(Node<T>* NP);///inserts nodes according to its priority
	int Dequeue();///deque from the beginning
	bool isempty();///checks if queue is empty or not
	void printlist();///print queue data
	int getcounter();///get number of data in queue
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
void priority_queue<T>::Enqueue(Node<T>* NP)
{
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
			if (NP->get_priority()>Front->get_priority())
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
int priority_queue<T>::Dequeue()
{
	if (isempty())
	{
		cout << "The queue is empty" << endl;
		c -= 1;
		return -1;
		
	}
	else if (Front == Rear)
	{
		delete Front;
		Front = Rear = nullptr;
		c -= 1;
		return -1;
		
	}
	else
	{
		Node<T>* helper = Front;
		int valueF = Front->get_data();
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
