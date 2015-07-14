/** ------------------------------------------------------------
* Singly Linked List declaration
* Alexander Karlsson, 2015-07-10
* -------------------------------------------------------------- */
#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H
#include <iostream>
#include "linkedlist.h"

template <typename T> 
class SinglyLinkedList : public LinkedList<T> {
public:

	SinglyLinkedList();
	~SinglyLinkedList();
	void push_back(const T t);
	void push_front(const T t);
	void insertAt(const int index, const T t);
	void pop_front(); 
	void pop_back();
	void removeAt(const int index);

};

#endif