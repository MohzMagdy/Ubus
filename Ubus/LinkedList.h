#pragma once
#include "Node.h"
#include <iostream>
#include <string>

using namespace std;

template<typename T>
class LinkedList
{
private:
	Node<T>* head;
	int count;
public:
	LinkedList();
	~LinkedList();
	Node<T>* get_head();
	void delete_all(); // Deletes all nodes
	void print_list(); // Prints all elements
	void insert_end(Node<T>* newNodePtr); // Inserts a node at the end
	void insert_end(T data); // Inserts a node at the end
	T delete_first(); // Deletes the first node
	void delete_node(T data); // Deletes the first node with the given data
	Node<T>* find(T data); // Returns a pointer to the node with the given data
	int getcounter();
	bool isempty();
	string getInsideIDs();
};

template<typename T>
LinkedList<T>::LinkedList()
{
	head = nullptr;
	count = 0;
}

template<typename T>
LinkedList<T>::~LinkedList()
{
	delete_all();
}

template<typename T>
Node<T>* LinkedList<T>::get_head()
{
	return head;
}

template<typename T>
void LinkedList<T>::delete_all()
{
	while (head)
	{
		delete_first();
	}
	count = 0;
}

template<typename T>
void LinkedList<T>::print_list()
{
	Node<T>* p = head;

	while (p)
	{
		cout << p->get_data() << " ";
		p = p->get_next();
	}
	cout << endl;
}

template<typename T>
string LinkedList<T>::getInsideIDs() {
	string insideIDs;
	Node<T>* tempPtr = head;
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
void LinkedList<T>::insert_end(Node<T>* newNodePtr)
{
	if (!head)
	{
		head = newNodePtr;
	}
	else
	{
		Node<T>* p = head;

		while (p)
		{
			p = p->get_next();
		}

		p->set_next(newNodePtr);
	}
	count++;
}

template<typename T>
void LinkedList<T>::insert_end(T data)
{
	Node<T>* newNodePtr = new Node<T>(data);

	if (!head)
	{
		head = newNodePtr;
	}
	else
	{
		Node<T>* p = head;

		while (p->get_next())
		{
			p = p->get_next();
		}

		p->set_next(newNodePtr);
	}
	count++;
}

template<typename T>
T LinkedList<T>::delete_first()
{
	if (!head) return NULL; // In case list is empty
	T data = head->get_data();
	Node<T>* p = head->get_next();
	delete head;
	head = p;
	count--;
	return data;
}

template<typename T>
void LinkedList<T>::delete_node(T data)
{
	if (!head) return; // In case list is empty
	if (head->get_data() == data) {
		delete_first();
		return;

	} // In case data is at head
		

	Node<T>* p = head->get_next();
	Node<T>* pPrev = head;

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

template<typename T>
Node<T>* LinkedList<T>::find(T data)
{
	Node<T>* p = head;
	while (p)
	{
		if (p->get_data() == data)
		{
			return p;
		}
		p = p->get_next();
	}
	return nullptr;
}

template<typename T>
int LinkedList<T>::getcounter()
{
	return count;
}
template<typename T>
bool LinkedList<T>::isempty() {
	if (head == nullptr) return true;
	else return false;
}