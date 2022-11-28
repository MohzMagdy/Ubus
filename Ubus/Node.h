#pragma once

template<typename T>
class Node
{
private:
	T data;
	Node* next;
	double pir;

public:
	Node();
	Node(T data);
	T get_data();
	Node* get_next();
	void set_data(T data);
	void set_next(Node* next);
	void set_priority(double pir);
	double get_priority();
};

template<typename T>
Node<T>::Node() 
{
	next = nullptr;
}

template<typename T>
Node<T>::Node(T data)
{
	this->data = data;
	next = nullptr;
}

template<typename T>
T Node<T>::get_data()
{
	return data;
}

template<typename T>
Node<T>* Node<T>::get_next()
{
	return next;
}

template<typename T>
void Node<T>::set_data(T data)
{
	this->data = data;
}

template<typename T>
void Node<T>::set_next(Node<T>* next)
{
	this->next = next;
}

template<typename T>
void Node<T>::set_priority(double pir) {
	this->pir = pir;
}

template<typename T>
double Node<T>::get_priority()
{
	return pir;
}