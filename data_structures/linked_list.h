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

	void push_front(T t) {
		//TODO
	}

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

	void insertAt(int index) {
		//TODO
		if (index == 0)
	}

	T removeFirst() {
		T t = first->value;
		first = first->next;
		--size;
		return t;		

	}

	T removeLast() {
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
			return removeLast();

		} else if (index == 0) {	
			return removeFirst();

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

			return t;
		}
	}


	T front() {
		return first->value;
	}

	T back() {
		return tail->value;
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