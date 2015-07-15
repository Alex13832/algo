/** ------------------------------------------------------------
* Implementation of a queue.
* Alexander Karlsson, 2015-07-15
* -------------------------------------------------------------- */
#ifndef QUEUE_H
#define QUEUE_H

#include "singly_linked_list.cc"

template <typename T> class Queue {

public:

	typedef T value_type;

	Queue() {}
	~Queue() { delete list; }

	/* Inserts item */
	void enqueue(T item) { list->push_back(item); }

	/* Returns the first element in the queue*/
	T peak() { return list->front(); }

	/* Returns and removes the first element in  the queue */
	T dequeue() {
		T item = list->front();
		list->pop_front();
		return item;
	}

	/* Returns the number of items in the queue */
	int height() { return list->length(); }

	bool empty() { return list->length() == 0; }


private:
	LinkedList<T> *list = new SinglyLinkedList<T>;
};

#endif