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
	void push_back(T t);
	void push_front(T t);
	void insertAt(int index, T t);
	void pop_front(); 
	void pop_back();
	void removeAt(int index);

};

#endif