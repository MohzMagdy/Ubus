#pragma once
#include "Node.h"
#include <iostream>

template<typename T>
class queue
{
private:
	Node<T>* Front;
	Node<T>* Rear;
	int count;
public:
	queue();
	~queue();
	void Enqueue(T data);///inserts nodes form the end
	T Dequeue();///deque from the beginning
	bool isempty();///checks if queue is empty or not
	void printlist();///print queue data
	int getcounter();
};


template<typename T>
queue<T>::queue()
{
	Front = nullptr;
	Rear = nullptr;
}

template<typename T>
queue<T>::~queue()
{
	while (!isempty())
		Dequeue(); // THIS DOES NOT DELETE THE ITEMS
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
void queue<T>::Enqueue(T data)
{
	Node<T>* NP = new Node<T>(data);
	if (isempty())
	{
		Front = Rear = NP;
	}
	else
	{
		Rear->set_next(NP);
		Rear = NP;
	}
	count++;
}

template<typename T>
T queue<T>::Dequeue()
{
	if (isempty())
	{
		cout << "The queue is empty" << endl;
		return NULL;
	}
	else if (Front == Rear)
	{
		T valueF = Front;
		delete Front;
		Front = Rear = nullptr;
		count--;
		return valueF;
	}
	else
	{
		Node<T>* helper = Front;
		T valueF = Front->get_data();
		Front = Front->get_next();
		count--;
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

template<typename T>
int queue<T>::getcounter()
{
	return count;
}