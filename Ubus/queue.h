#pragma once
#include "Node.h"
#include <iostream>

template<typename T>
class queue
{
private:
	Node<T>* Front;
	Node<T>* Rear;
public:
	queue();
	void Enqueue(Node<T>* NP);///inserts nodes form the end
	int Dequeue();///deque from the beginning
	bool isempty();///checks if queue is empty or not
	void printlist();///print queue data
};


template<typename T>
queue<T>::queue()
{
	Front = nullptr;
	Rear = nullptr;
}

template<typename T>
bool queue<T>::isempty()
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
void queue<T>::Enqueue(Node<T>* NP)
{
	if (isempty())
	{
		Front = Rear = NP;
	}
	else
	{
		Rear->set_next(NP);
		Rear = NP;
	}
}

template<typename T>
int queue<T>::Dequeue()
{
	if (isempty())
	{
		cout << "The queue is empty" << endl;
		return -1;
	}
	else if (Front == Rear)
	{
		delete Front;
		Front = Rear = nullptr;
		return -1;
	}
	else
	{
		Node<T>* helper = Front;
		int valueF = Front->get_data();
		Front = Front->get_next();
		return valueF;

	}
}
template<typename T>
void queue<T>::printlist()
{
	Node<T>* temp = Front;
	while (temp != nullptr)
	{
		cout << temp->get_data() << " ";
		temp = temp->get_next();
	}
	cout << endl;
}
