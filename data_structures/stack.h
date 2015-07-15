/** ------------------------------------------------------------
* Implementation of a stack.
* Alexander Karlsson, 2015-07-15
* -------------------------------------------------------------- */
#ifndef STACK_H
#define STACK_H

#include "singly_linked_list.cc"

template <typename T> class Stack {

public:

	typedef T value_type;

	Stack() {} //{ *list = new SinglyLinkedList<T>; };

	~Stack() {delete list; }

	/* Add new item onto stack */
	void push(T item) { list->push_front(item); }

	/* Return the top element of the stack*/
	T peak() { return list->front(); }

	/* Return and remove the top element of the stack*/
	T pop() {
		T item = list->front();
		list->pop_front();
		return item;
	}

	/* Returns the number of item on the stack*/
	int height() { return list->length();}

	bool empty() {return list->length() == 0;}
	

private:
	LinkedList<T> *list = new SinglyLinkedList<T>;
};

#endif