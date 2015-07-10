/** -------------------------------------------------------
* Singly Linked List declaration
* Alexander Karlsson, 2015-07-10
* --------------------------------------------------------- */
#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H
#include <iostream>
#include "linkedlist.h"

template <typename T> class SinglyLinkedList : public LinkedList<T> {
public:

	typedef T value_type;

	/* Constructor */
	SinglyLinkedList();
	void init();
	void push_back(T t);
	void push_front(T t);
	void insertAt(int index, T t);
	void pop_front(); 
	void pop_back();
	void removeAt(int index);
	T front();
	T back();
	T at(int index);
	int length();
	/* Prints the element at every node */
	void print();

private:
	Node<T> *first = new Node<T>,*tail = new Node<T>;
	int size = 0;
};

#endif