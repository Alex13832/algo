/** -------------------------------------------------------
* Doubly Linked List declaration
* Alexander Karlsson, 2015-07-12
* --------------------------------------------------------- */
#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
#include <iostream>
#include "linkedlist.h"

template <typename T> class DoublyLinkedList : public LinkedList<T> {
public:

	typedef T value_type;

	/* Constructor */
	DoublyLinkedList();
	void init();
	void push_back(T t);
	void push_front(T t);
	void insertAt(int index, T t);
	void pop_front(); 
	void pop_back();
	void removeAt(int index);
	void clear();
	T front();
	T back();
	T at(int index);
	int length(); 
	/* Prints the element at every node */
	void print();
	void print_rev();

private:
	Node<T> *first = new Node<T>, *tail = new Node<T>;
	int size = 0;
};

#endif