/** ------------------------------------------------------------
* Implementation of member functions for DynArray
* Alexander Karlsson, 2015-07-25
* -------------------------------------------------------------- */
#include "dyn_array.h"
#include <iostream>
#include <cmath>
using namespace std;

template <typename T>
DynArray<T>::DynArray(initializer_list<T> lst) {

	for (auto item: lst) {
		if (index >= limit) resize(limit*2);

		items[index] = item;
		index++;
	}
}

template <typename T>
DynArray<T>::DynArray(const size_t s) {
	for (size_t i = 0; i < s; i++) {
		push_back(0);
	}
} 

template <typename T>
DynArray<T>::DynArray(const size_t s, const T item) {
	for (size_t i = 0; i < s; i++) {
		push_back(item);
	}
}

template <typename T>
void DynArray<T>::push_back(T item) {
	if (index >= limit) resize(limit*2);
	
	items[index] = item;
	index++;
}

template <typename T>
void DynArray<T>::pop_back() {
	if (index != 0) {
		items[index] = 0;
		index--;
		
		if (index < floor(limit/2)) resize(limit/2);
	}
}

template <typename T>
void DynArray<T>::removeAt(const int pos) {
	for ( size_t i = pos; i < index; i++) {
		items[i-1] = items[i];
	}
	items[index] = 0;
	index--;
}

template <typename T>
void DynArray<T>::resize(size_t s) {
	limit = s;
	T* temp = new T[limit];
 
 	for (size_t i = 0; i < index; i++) {
		temp[i] = items[i];
	}
	
	delete items;
	items = temp;
	
}

template <typename T>
void DynArray<T>::printAll() {

	for (size_t i = 0; i < index; i++){
		cout << items[i] << " ";
	}
	
	cout << endl;

}