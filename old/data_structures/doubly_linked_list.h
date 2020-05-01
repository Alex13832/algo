/** ------------------------------------------------------------
* Doubly Linked List declaration
* Alexander Karlsson, 2015-07-12
* -------------------------------------------------------------- */
#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
#include <iostream>
#include "linkedlist.h"

template <typename T> 
class DoublyLinkedList : public LinkedList<T> {
public:
	
	DoublyLinkedList();
	~DoublyLinkedList();
	void push_back(T t);
	void push_front(T t);
	void insertAt(int index, T t);
	void pop_front(); 
	void pop_back();
	void removeAt(int index);
	void swap(int index);


};

#endif