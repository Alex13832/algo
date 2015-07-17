/** ------------------------------------------------------------
* Self Oganizing lists implementations
* Alexander Karlsson, 2015-07-17
* -------------------------------------------------------------- */
#include "self_organizing_list.h"
#include <iostream>
using namespace std;

/* Move to front method implementation */

template <typename T>
T SOListFront<T>::operator[](int k) {
	if (k >= this->size()) return 0;
	
	T item = this->list->at(k);

	if (k > 0) {
		this->list->removeAt(k);
		this->list->push_front(item);
	}

	return item;
}

/* Count method implementation */

template <typename T>
T SOListCount<T>::operator[](int k) {
	if (k >= this->size()) return 0;

	if (k == 0) {
		counter[this->list->at(k)]++;
		return this->list->at(k);
	}

	T item = this->list->at(k);
	counter[item]++;

	if (counter[item] > counter[this->list->at(k-1)]) {
		this->list->swap(k);
	}

	return item;

}

/* Transpose method */ 

template <typename T>
T SOListTranspose<T>::operator[](int k) {
	if (k >= this->size()) return 0;

	T item = this->list->at(k);

	if (k > 0) this->list->swap(k);

	return item;
}