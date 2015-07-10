/** -------------------------------------------------------
* Singly Linked List implementation
* Alexander Karlsson, 2015-07-10
* --------------------------------------------------------- */
#include "singly_linked_list.h"
using namespace std;

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList() {
	init();
}

template <typename T>
void SinglyLinkedList<T>::init() {
	first = tail;
	tail->next = NULL;
}

template <typename T>
void SinglyLinkedList<T>::push_back(T t) {
	if(size == 0) {
		init(); // Same as callaing constructor
	} else {
		Node<T> *temp = new Node<T>;
		temp->value = t;
		tail->next = temp;
		tail = temp;
	}
	size++;
}

template <typename T>
void SinglyLinkedList<T>::push_front(T t) {
	if (size == 0) {
		init();
	}

	Node<T> *node = new Node<T>;
	node->value = t;
	node->next = first;
	first = node;
	size++;
}

template <typename T>
void SinglyLinkedList<T>::insertAt(int index, T t)  {
	if (index == 0) { 
		push_front(t); // case already implmented
	} else if (index >= size) {
		push_back(t); // This case also

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

template <typename T>
void SinglyLinkedList<T>::pop_front() {
	if (size == 0) { 
		return; // Trying to remove from an empty list
	}

	/* Special case when size == 1 */
	if (size == 1) {
		first = NULL; 
		--size;
		return;
	}

	first = first->next;
	--size;	
}

template <typename T>
void SinglyLinkedList<T>::pop_back() {
	if (size == 0) {
		return; // Trying to remove from an empty list
	}

	/* Special case when size == 1 */
	if (size == 1) {
		first = NULL;
		--size;
		return;
	}

	Node<T> *temp = first;
	while (temp->next) {
		tail = temp;
		temp = temp->next;
	}
	
	--size;

	tail->next = NULL;	
}

template <typename T>
void SinglyLinkedList<T>::removeAt(int index) {
	/* same as calling pop_back() */
	if (index >= size) {
		--size;
		pop_back();

	/* same as calling pop_front() */
	} else if (index == 0) {
		--size;	
		pop_front();

	} else {
		Node<T> *temp1 = first, *temp2 = first;
		int k = 0;
		while (k!=index) {
			k++;
			temp2 = temp1;
			temp1 = temp1->next;
		} 

		temp2->next = temp1->next;
		--size;
	}
}

template <typename T>
T SinglyLinkedList<T>::front() {
	return first->value;
}

template <typename T>
T SinglyLinkedList<T>::back() {
	return tail->value;
}

template <typename T>
T SinglyLinkedList<T>::at(int index) {
	int k = 0;
	Node<T> *node = first;

	if (k == index) return first->value;

	while ( k!= index ) {
		k++;
		node = node->next;
	}

	return node->value;
}

template <typename T>
int SinglyLinkedList<T>::length() {
	return size;
}

template <typename T>
void SinglyLinkedList<T>::print() {
	Node<T> *temp = first;
	while (temp) {
		std::cout << temp->value << std::endl;
		temp = temp->next;
	}
}

