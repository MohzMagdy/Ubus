#pragma once
#include "Node.h"
#include <iostream>
#include <string>
using namespace std;

template<typename T>
class queue
{
private:
	Node<T>* Front;
	Node<T>* Rear;
	int count = 0;
public:
	queue();
	~queue();
	void Enqueue(T data);///inserts nodes form the end
	T Dequeue();///deque from the beginning
	bool Dequeue(T&);
	bool isempty();///checks if queue is empty or not
	void printlist();///print queue data
	int getcounter();
	void Peek(T& data) ;/// get the front data without delete from the qeue
	Node<T>* ReturnFront(); /// returns front node
	void delete_data(T data);/// deletes specific data
	string getInsideIDs();
	string getInsideIDsExceptFirst();
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
		T valueF = Front->get_data();
		delete Front;
		Front = Rear = nullptr;
		count--;
		return valueF;
	}
	else
	{
		Node<T>* helper = Front;
		T valueF = Front->get_data();
		helper = Front->get_next();
		delete Front;
		Front = helper;
		count--;
		return valueF;
	}
}

template <typename T>
bool queue<T>::Dequeue(T& value) {
	if (isempty())
		return false;

	value = Front->get_data();
	Node<T>* tempNode = Front;
	Front = Front->get_next();
	delete tempNode;
	this->count -= 1;

	if (this->Front == nullptr)
		this->Rear = nullptr;

	return true;
}

template<typename T>
string queue<T>::getInsideIDs() {
	string insideIDs;
	Node<T>* tempPtr = this->Front;
	while (tempPtr != nullptr)
	{
		insideIDs += to_string(tempPtr->get_data()->Get_ID());
		if (tempPtr->get_next() != nullptr) {
			insideIDs += ",";
		}
		tempPtr = tempPtr->get_next();
	}
	return insideIDs;
}

template<typename T>
string queue<T>::getInsideIDsExceptFirst() {
	string insideIDs;
	Node<T>* tempPtr = this->Front;
	while (tempPtr != nullptr)
	{
	insideIDs += to_string(tempPtr->get_data()->getID());
	tempPtr = tempPtr->get_next();
	}
	return insideIDs;
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

template<typename T>
void queue<T>::Peek(T& data)
{
	if (isempty()) {
		data = nullptr;
		return;
	}
	data = Front->get_data();
}

template<typename T>
inline Node<T>* queue<T>::ReturnFront()
{
	return Front;
}

template<typename T>
inline void queue<T>::delete_data(T data)
{
	if (isempty())
	{
		return;
	}
	if (Front->get_data() == data)
	{
		Dequeue();
		return;
	}
	Node<T>* p = Front->get_next();
	Node<T>* pPrev = Front;

	while (p)
	{
		if (p->get_data() == data)
		{
			pPrev->set_next(p->get_next());
			delete p;
			count--;
			return;
		}
		pPrev = p;
		p = p->get_next();
	}
}
