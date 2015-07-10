/** -------------------------------------------------------
* Singly Linked List implementation
* Alexander Karlsson, 2015-07-10
* --------------------------------------------------------- */
#ifndef LinkedList_H
#define LinkedList_H
#include <iostream>
#include <iterator>
#include "node.h"

template <typename T> class LinkedList {
public:

	typedef T value_type;

	LinkedList() {
		first = tail;
		tail->next = NULL;
	}

	/* Inserts an element t at the back of the list*/
	void push_back(T t) {
		if(size == 0) {
			first->value = t;
			first->next = tail;
		} else {
			Node<T> *temp = new Node<T>;
			temp->value = t;
			tail->next = temp;
			tail = temp;
		}
		size++;
	}

	/* Inserts an element t at the front of the list*/
	void push_front(T t) {
		Node<T> *node = new Node<T>;
		node->value = t;
		node->next = first;
		first = node;
		size++;
	}

	/* Inserts an element t at a given index*/
	void insertAt(int index, T t) {
		if (index == 0) {
			push_front(t);
		} else if (index >= size) {
			push_back(t);

		} else {

			Node<T> *node = new Node<T>, *temp1 = first, *temp2 = first;
			node->value = t;
			int k = 0;
			while (k != index) {
				k++;
				temp1 = temp2;
				temp2 = temp2->next;
			}

			temp1->next = node;
			node->next = temp2;

		}
		++size;
	}

	/* Removes and returns the front element */
	T pop_front() {
		T t = first->value;
		first = first->next;
		--size;
		return t;		

	}

	/* Removes and returns the last element of the list*/
	T pop_back() {
		T t = tail->value;
		--size;

		Node<T> *temp = first;
		while (temp->next) {
			tail = temp;
			temp = temp->next;
			
		}
		tail->next = NULL;

		return t;
	}

	/** Removes at a given index, if index > size, the last item
	 is removed.*/ 
	T removeAt(int index) {
		if (index >= size) {
			--size;
			return pop_back();

		} else if (index == 0) {
			--size;	
			return pop_front();

		} else {
			Node<T> *temp1 = first, *temp2 = first;
			int k = 0;
			while (k!=index) {
				k++;
				temp2 = temp1;
				temp1 = temp1->next;
			} 

			T t = temp1->value;
			temp2->next = temp1->next;
			--size;
			return t;
		}
	}

	/* Returns the first element */
	T front() {
		return first->value;
	}

	/* Returns the last element */
	T back() {
		return tail->value;
	}

	/* Returns the element at index */
	T at(int index) {
		int k = 0;
		Node<T> *node = first;

		if (k==index) return first->value;

		while ( k!= index ) {
			k++;
			node = node->next;
		}

		return node->value;
	}

	/* Returns the length of the list */
	int length() {
		return size;
	}

	void print() {
		Node<T> *temp = first;
		while (temp) {
			std::cout << temp->value << std::endl;
			temp = temp->next;
		}
	}

private:
	Node<T> *first = new Node<T>,*tail = new Node<T>;
	int size = 0;
};

#endif