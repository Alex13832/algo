/** -------------------------------------------------------
* Doubly Linked List implementation
* Alexander Karlsson, 2015-07-12
* --------------------------------------------------------- */
#include "doubly_linked_list.h"
using namespace std;

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() {
	first = NULL;
}

template <typename T>
void DoublyLinkedList<T>::init() {
	tail = new Node<T>;
	first = tail;
	tail->next = NULL;
	first->prev = NULL;
	
}

template <typename T>
void DoublyLinkedList<T>::push_back(T t) {
	if (size == 0){ 
		init();
		first->value = t;
	} else {	
		
	
	
	Node<T> *temp = new Node<T>;
	temp->value = t;
	temp->prev = tail;
	tail->next = temp;
	tail = temp;	
	
	}	
	++size;
}

template <typename T>
void DoublyLinkedList<T>::push_front(T t) {
	if (size == 0) {
		init();
		first->value = t;
	} else {
		Node<T> *temp = new Node<T>;
		temp->value = t;
		temp->next = first;
		first->prev = temp;
		first = temp;
	} 

	++size;
}

template <typename T>
void DoublyLinkedList<T>::insertAt(int index, T t)  {
	if (size == 0) {
		init();
		first->value = t;
	
	} else  if (index >= size) {
		push_back(t);
		return;

	} else if (index == 0) {
		push_front(t);
		return;

	} else {
		int k = 0;
		Node<T> *mid = new Node<T>, *temp = first;
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

	++size;
}

template <typename T>
void DoublyLinkedList<T>::pop_front() {
	if (size == 0) {
		first = NULL;
		tail = NULL;
		return;
	}

	if (size == 1) {
		first = NULL;
		tail = NULL;
		--size;
		return;
	} 

	
	first = first->next;
	first->prev = NULL;
	--size;
}

template <typename T>
void DoublyLinkedList<T>::pop_back() {
	if (size == 0) {
		first = NULL;
		tail = NULL;
		return;
	}

	if (size == 1) {
		first = NULL;
		tail = NULL;
		--size;
		return;
	}

	tail = tail->prev;
	tail->next = NULL;
	--size;
}

template <typename T>
void DoublyLinkedList<T>::removeAt(int index) {
	if (size == 0) {
		first = NULL;
		tail = NULL;
		return;
	}

	if (index > size-1) {
		return; // Should not remove something	
	}

	if (index == 0) {
		pop_front(); //case already implemented
		return;
	}

	if(index == size-1) {
		pop_back(); //case already implemented
		return;
	}

	int k = 0;
	Node<T> *temp = first;
	while (k != index-1) {
		k++;
		temp = temp->next;
	}

	temp->next = temp->next->next;
	temp->next->prev = temp;
	--size;

}

template <typename T>
void DoublyLinkedList<T>::clear() {
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
T DoublyLinkedList<T>::front() {
	return first->value;
}

template <typename T>
T DoublyLinkedList<T>::back() {
	return tail->value;
}

template <typename T>
T DoublyLinkedList<T>::at(int index) {
	/* Let the return value for these two cases be 0s*/
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
int DoublyLinkedList<T>::length() {
	return size;
}

template <typename T>
void DoublyLinkedList<T>::print() {
	Node<T> *temp = first;
	while (temp) {
		cout << temp->value << endl;
		temp = temp->next;
	}
}

template <typename T>
void DoublyLinkedList<T>::print_rev() {
	Node<T> *temp = tail;
	while (temp) {
		cout << temp->value << endl;
		temp = temp->prev;
	}
}


