#pragma once
#include "Node.h"
#include "normal.h"
#include "special.h"
#include "VIP.h"
#include "people.h"
#include <iostream>

template<typename T>
class Priority_queue
{
private:
	Node<T>* Front;
	Node<T>* Rear;
	Node<T>* pr;
public:
	Priority_queue();
	void Enqueue(Node<T>* NP);
	int Dequeue();
	bool isempty();
	void printlist();
};

template<typename Base, typename T>
inline bool instanceof(const T* ptr) {
	return dynamic_cast<const Base*>(ptr);
}

template<typename T>
Priority_queue<T>::Priority_queue()
{
	Front = nullptr;
	Rear = nullptr;
	pr = nullptr;
}

template<typename T>
bool Priority_queue<T>::isempty()
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
void Priority_queue<T>::Enqueue(Node<T>* NP)
{
	if (isempty())
	{
		Front = Rear = pr = NP;
	}
	else
	{
		Rear->set_next(NP);
		Rear = NP;
		/*if ((instanceof<VIP>(NP)) && (instanceof<special>(pr)))
		{
			pr = NP;
		}
		else if ((instanceof<VIP>(NP)) && (instanceof<normal>(pr)))
		{
			pr = NP;
		}
		else if ((instanceof<special>(NP)) && (instanceof<normal>(pr)))
		{
			pr = NP;
		}*/
	}
}

template<typename T>
int Priority_queue<T>::Dequeue()
{
	if (isempty())
	{
		cout << "The queue is empty" << endl;
		return -1;
	}
	else if (Front == Rear)
	{
		delete Front;
		Front = Rear = pr = nullptr;
		return -1;
	}
	else
	{
		Node<T>* helper = Front;
		/*Node<T>* temp1 = Front;
		Node<T>* temp2 = Front;
		Node<T>* temp3 = Front;*/
		int valueF = Front->get_data();
		Front = Front->get_next();

		/*while (pr!=nullptr || temp1!=nullptr)
		{
			if (instanceof<VIP> (temp1))
			{
				pr = temp1;
			}
			temp1 = temp1->get_next();
		}
		while (pr!=nullptr || temp2!=nullptr)
		{
			if (instanceof<special> (temp2))
			{
				pr = temp2;
			}
			temp2 = temp2->get_next();
		}
		while (pr != nullptr || temp3 != nullptr)
		{
			if (instanceof<normal> (temp3))
			{
				pr = temp3;
			}
			temp3 = temp3->get_next();
		}*/
		return valueF;

	}
}
template<typename T>
void Priority_queue<T>::printlist()
{
	Node<T>* temp = Front;
	while (temp != nullptr)
	{
		cout << temp->get_data() << " ";
		temp = temp->get_next();
	}
	cout << endl;
}
