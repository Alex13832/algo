/** ------------------------------------------------------------
* Implementation of BinaryHeap functions
* Alexander Karlsson, begun 2015-07-26
* -------------------------------------------------------------- */
#include "binary_heap.h"
#include <cmath>
using namespace std;

template <typename T>
void BinaryHeap<T>::push(T item) {
	array->push_back(item);
	size++;
	percolate_up(size-1);
}

template <typename T>
T BinaryHeap<T>::pop() {
	T item = (*array)[0];
	(*array)[0] = array->back();
	array->pop_back();
	size--;

	/* Move item if its value is > than child's */
	percolate_down(0);

	return item;
}

template <typename T>
void BinaryHeap<T>::heapify(vector<T> vec) {
	for (auto item: vec) {
		push(item); //Quick-fix?
	}
}

template <typename T>
void BinaryHeap<T>::percolate_up(int k) {
	if (k == -1) return; //base case

	/** The recursive call will continue until no parent's
	value is greater than a child's*/
	if ((*array)[parent(k)] > (*array)[k]) {
		T item = (*array)[parent(k)];
		(*array)[parent(k)] = (*array)[k];
		(*array)[k] = item;

		percolate_up(parent(k)); //Continue percolating
	}

}

template <typename T>
void BinaryHeap<T>::percolate_down(int k) {

	int child_index = child_left(k)-1, index = k;

	for (int i = 1; i <= 2; i++) {

		if (child_index + i <= size) {
			if ((*array)[index] > (*array)[child_index+i]) {
				index = child_index+i;
			}
		}
	}

	if (index != k) {
		swap((*array)[k],(*array)[index]);
		percolate_down(index);
	}

}

template <typename T>
int BinaryHeap<T>::parent(int k) {
	return floor((k-1)/2);
}

template <typename T>
int BinaryHeap<T>::child_left(int k) {
	return 2*k+1;
}

template <typename T>
int BinaryHeap<T>::child_right(int k) {
	return 2*k+2;
}

template <typename T>
void BinaryHeap<T>::printAll() {
	for (auto item: *array) {
		cout << item << " ";
	}
	cout << endl;
}