#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include "node.h"

template <typename T>  class LinkedList {
public:

	typedef T value_type;
	/* Reuse of code in constructor here */
	virtual void init() = 0;
	/* Inserts an element t at the back of the list*/
	virtual void push_back(T t) = 0;
	/* Inserts an element t at the front of the list*/
	virtual void push_front(T t) = 0;
	/* Inserts an element t at a given index*/
	virtual void insertAt(int index, T t) = 0;
	/* Removes the front element */
	virtual void pop_front() = 0;
	/* Removes the last element of the list*/
	virtual void pop_back() = 0;
	/* Removes at a given index */
	virtual void removeAt(int index) = 0;
	/* Returns the first element */
	virtual T front() = 0;
	/* Returns the last element */
	virtual T back() = 0;
	/* Returns the element at index */
	virtual T at(int index) = 0;
	/* Returns the length of the list */
	virtual int length() = 0;

};


#endif