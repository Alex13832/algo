/** ------------------------------------------------------------
* Doubly Linked List implementation
* Alexander Karlsson, 2015-07-12
* -------------------------------------------------------------- */
#include "doubly_linked_list.h"
#include "linked_list.cc"
using namespace std;

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() {
	this->first = NULL;
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
	Node<T> *temp = this->first, *old;
	while (temp) {
		old = temp;
		temp = temp->next;
		delete old;
		old = NULL;
	}

	this->first = NULL;
	this->tail = NULL;
}

template <typename T>
void DoublyLinkedList<T>::push_back(T t) {
	if (this->size == 0){ 
		LinkedList<T>::init();
		this->first->value = t;
	} else {	
		
	
	
	Node<T> *temp = new Node<T>;
	temp->value = t;
	temp->prev = this->tail;
	this->tail->next = temp;
	this->tail = temp;	
	
	}	
	++this->size;
}

template <typename T>
void DoublyLinkedList<T>::push_front(T t) {
	if (this->size == 0) {
		LinkedList<T>::init();
		this->first->value = t;
	} else {
		Node<T> *temp = new Node<T>;
		temp->value = t;
		temp->next = this->first;
		this->first->prev = temp;
		this->first = temp;
	} 

	++this->size;
}

template <typename T>
void DoublyLinkedList<T>::insertAt(int index, T t)  {
	if (this->size == 0) {
		LinkedList<T>::init();
		this->first->value = t;
	
	} else  if (index >= this->size) {
		push_back(t);
		return;

	} else if (index == 0) {
		push_front(t);
		return;

	} else {
		int k = 0;
		Node<T> *mid = new Node<T>, *temp = this->first;
		mid->value = t;
		while (k != index) {
			temp = temp->next;
			k++;
		}

		mid->next = temp;
		mid->prev = temp->prev;
		temp->prev->next = mid;
		temp->prev = mid;
	}

	++this->size;
}

template <typename T>
void DoublyLinkedList<T>::pop_front() {
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
	this->first->prev = NULL;
	--this->size;
}

template <typename T>
void DoublyLinkedList<T>::pop_back() {
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

	this->tail = this->tail->prev;
	this->tail->next = NULL;
	--this->size;
}

template <typename T>
void DoublyLinkedList<T>::removeAt(int index) {
	if (this->size == 0) {
		this->first = NULL;
		this->tail = NULL;
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
	temp->next->prev = temp;
	--this->size;

}

template <typename T>
void DoublyLinkedList<T>::swap(int index) {
	if (index == 0) return;

	if (index == 1) {
		T item = this->at(1);
		this->removeAt(1);
		this->push_front(item);
		return;
	}

	Node<T> *post = this->first, *pre;
	if (index < (this->size)-1) {

		int k = 0;

		while (k != index) {
			pre = post;
			post = post->next;
			k++;
		}
		
		Node<T> *temp;

		temp = post->next;
		pre->prev->next = post;
		post->prev = pre->prev;

		post->next = pre;
		pre->prev = post;
	
		pre->next = temp;
		temp->prev = pre;
	
	} else {
		T item = this->back();
		this->pop_back();
		this->insertAt(this->size-1,  item);
	}
}