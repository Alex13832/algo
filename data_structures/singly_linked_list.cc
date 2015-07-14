/** ------------------------------------------------------------
* Singly Linked List implementation
* Alexander Karlsson, 2015-07-10
* -------------------------------------------------------------- */
#include "singly_linked_list.h"
#include "linked_list.cc"
using namespace std;

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList() {
	this->first = NULL;
}

template <typename T>
void SinglyLinkedList<T>::push_back(T t) {
	if(this->size == 0) {
		LinkedList<T>::init();
		this->first->value = t;
	} else {
		Node<T> *temp = new Node<T>;
		temp->value = t;
		this->tail->next = temp;
		this->tail = temp;
	}
	this->size++;
}

template <typename T>
void SinglyLinkedList<T>::push_front(T t) {
	if (this->size == 0) {
		LinkedList<T>::init();
		this->first->value = t;
	} else {
		Node<T> *node = new Node<T>;
		node->value = t;
		node->next = this->first;
		this->first = node;	
	}
	
	this->size++;
}

template <typename T>
void SinglyLinkedList<T>::insertAt(int index, T t)  {
	if (index == 0) { 
		push_front(t); // case already implmented
	} else if (index >= this->size) {
		push_back(t); // This case also

	} else {

		Node<T> *node = new Node<T>, *temp1 = this->first, *temp2 = this->first;
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
	++this->size;
}

template <typename T>
void SinglyLinkedList<T>::pop_front() {
	if (this->size == 0) {
		this->first = NULL;
		this->tail = NULL;
		return;
	}

	if (this->size == 1) {
		this->first = NULL;
		this->tail = NULL;
		--this->size;
		return;
	} 

	this->first = this->first->next;
	--this->size;
}

template <typename T>
void SinglyLinkedList<T>::pop_back() {
	if (this->size == 0) {
		return; // Trying to remove from an empty list
	}

	/* Special case when size == 1 */
	if (this->size == 1) {
		this->first = NULL;
		--this->size;
		return;
	}

	Node<T> *temp = this->first;
	while (temp->next) {
		this->tail = temp;
		temp = temp->next;
	}
	
	--this->size;

	this->tail->next = NULL;	
}

template <typename T>
void SinglyLinkedList<T>::removeAt(int index) {
		if (this->size == 0) {
		this->first = NULL;
		this->tail = NULL;
		return;
	}

	if (this->size == 1 && index == this->size-1) {
		this->first = NULL;
		this->tail = NULL;
		--this->size;
		return;
	}

	if (index > this->size-1) {
		return; // Should not remove something	
	}

	if (index == 0) {
		pop_front(); //case already implemented
		return;
	}

	if(index == this->size-1) {
		pop_back(); //case already implemented
		return;
	}

	int k = 0;
	Node<T> *temp = this->first;
	while (k != index-1) {
		k++;
		temp = temp->next;
	}

	temp->next = temp->next->next;
	--this->size;
}
