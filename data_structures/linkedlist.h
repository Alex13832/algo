/** ------------------------------------------------------------
* Abstract class for LinkedList
* Alexander Karlsson, 2015-07-14
* -------------------------------------------------------------- */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include "node.h"

template <typename T>  
class LinkedList {

public:

	typedef T value_type;
	
	virtual ~LinkedList() = 0;
	void init();
	/* Clears the list */
	void clear();
	/* Returns the first element */
	T front();
	/* Returns the last element */
	T back();
	/* Returns the element at index */
	T at(const int index);
	/* Returns the length of the list */
	int length();
	/* Inserts an element t at the back of the list*/
	virtual void push_back(const T t) = 0;
	/* Inserts an element t at the front of the list*/
	virtual void push_front(const T t) = 0;
	/* Inserts an element t at a given index*/
	virtual void insertAt(const int index, const T t) = 0;
	/* Removes the front element */
	virtual void pop_front() = 0;
	/* Removes the last element of the list*/
	virtual void pop_back() = 0;
	/* Removes at a given index */
	virtual void removeAt(const int index) = 0;

	void print();
	void print_rev();

protected:
	Node<T> *first = new Node<T>, *tail = new Node<T>;
	int size = 0;
};

#endif