/** ------------------------------------------------------------ 
* Implentation of non-abstract methods in LinkedList
* Alexander Karlsson, 2015-07-14
* -------------------------------------------------------------- */
#include "linkedlist.h"
using namespace std;

template <typename T>
LinkedList<T>::~LinkedList() {
	Node<T> *temp = this->first, *old;
	while (temp) {
		old = temp;
		temp = temp->next;
		delete old;
		old = NULL;
	}
	delete this->first;
	delete this->tail;
	this->first = NULL;
	this->tail = NULL;
}

template <typename T>
void LinkedList<T>::init() {
	tail = new Node<T>;
	first = tail;
	tail->next = NULL;
}

template <typename T>
void LinkedList<T>::clear() {
	Node<T> *temp = first, *old;
	while (temp) {
		old = temp;
		temp = temp->next;
		delete old;
		old = NULL;
}

	first = NULL;
	tail = NULL;
	size = 0;
}

template <typename T>
T LinkedList<T>::front() {
	return first->value;
}

template <typename T>
T LinkedList<T>::back() {
	return tail->value;
}

template <typename T>
T LinkedList<T>::at(const int index) {
	if ((size == 0) || (index >= size)) return 0;

		int k = 0;
		Node<T> *temp = first;
		while (k != index) {
			k++;
			temp = temp->next;
	} 

	return temp->value;
}

template <typename T>
int LinkedList<T>::length() {
	return size;
}

template <typename T>
void LinkedList<T>::print() {
	Node<T> *temp = first;
	while (temp) {
		cout << temp->value << endl;
		temp = temp->next;
	}
}


template <typename T>
void LinkedList<T>::print_rev() {
	Node<T> *temp = tail;
	while (temp) {
		cout << temp->value << endl;
		temp = temp->prev;
	}
}

/*
iterator begin() {
	return first->value;
}

iterator end() {
	return tail->end;
}

*/